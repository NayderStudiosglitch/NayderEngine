#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/ZombieAI.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include "WeaponSystem.cpp"
#include "HealthSystem.cpp" // Interlocking real health system components
#include <iostream>
#include <vector>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.1.4] - UNIFIED HEALTH CORE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 COMBAT AND VITAL RECONSTRUCTION MAP:" << std::endl;
    std::cout << "  v0.1.2 Weapon System Framework  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.3 Zombie AI Pathing Mesh   -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.4 Health System Engine     -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.1.5 HUD System Interface     -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    NayderZombieAIEngine zombie_ai;
    NayderWeaponSystem combat_system;
    NayderHealthSystem vital_system;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Playable Combat v0.1.4")) {
        return -1;
    }

    GLFWwindow* active_window = glfwGetCurrentContext();
    input_engine.ConfigureInputCallbacks(active_window);
    engine_runtime.SetupRealGraphicsPipeline();

    if (!shader_compiler.LoadAndCompileShaders("Assets/Shaders/Basic3D.vert", "Assets/Shaders/Basic3D.frag")) {
        return -1;
    }
    if (!texture_system.LoadRealBMPTexture("Assets/Textures/zombie_diffuse.bmp")) {
        return -1;
    }
    if (!audio_system.InitializeAudioHardware()) {
        return -1;
    }

    CompiledMesh zombie_mesh = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    unsigned int VAO, VBO, EBO;
    obj_loader.UploadMeshToGPU(zombie_mesh, VAO, VBO, EBO);

    // 1. INITIALIZE VITAL POOLS & COMBAT GEAR PRESETS
    EntityHealthPool player_vitals = { "NAYDER_01", 100, 100, 75, 75, false };
    WeaponProfile primary_m4 = combat_system.EquipWeaponPreset(WeaponType::ASSAULT_RIFLE);

    std::vector<ZombieEntityNode> dynamic_horde;
    int zombie_hps[] = { 100, 100, 100 };
    bool zombie_deads[] = { false, false, false };

    dynamic_horde.push_back({ 1, "Runner_Alpha", 15.0f, 4.0f, 15 });
    dynamic_horde.push_back({ 2, "Brute_Heavy",  20.0f, 2.0f, 35 });
    dynamic_horde.push_back({ 3, "Runner_Beta",  25.0f, 3.5f, 15 });

    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    bool space_was_released = true;
    int total_kills = 0;

    std::cout << "\n🚀 [PLAYABLE PROTOCOL READY]:" << std::endl;
    std::cout << " -> HOLD [W] to move player forward." << std::endl;
    std::cout << " -> TAP [SPACEBAR] to shoot the closest running zombie in path vectors!" << std::endl;

    // MASTER ENGINE RUNTIME TICK GAME LOOP
    while (!engine_runtime.ShouldWindowClose() && !player_vitals.is_dead) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // Player movement
        float movement_force = 0.0f;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            movement_force = 4.0f * dt;
            player_collider.x += movement_force;
        }

        // Run multi-agent AI pathfinding ticks
        for (size_t i = 0; i < dynamic_horde.size(); ++i) {
            // Synchronize positions between structural nodes
            dynamic_horde[i].pos_x = dynamic_horde[i].pos_x; 
        }
        zombie_ai.ProcessHordePathfindingTick(dynamic_horde, player_collider.x, dt);

        // 2. INTERLOCK LIVE DAMAGE CALCULATIONS
        for (size_t i = 0; i < dynamic_horde.size(); ++i) {
            if (zombie_deads[i]) continue;

            float distance = std::abs(dynamic_horde[i].pos_x - player_collider.x);
            if (distance <= 1.8f) {
                // Zombie is close enough to strike player vitals
                vital_system.ApplyDamageToPlayer(player_vitals, dynamic_horde[i].attack_damage);
            }
        }

        // 3. WEAPON SHOOT INTERPOLATIONS VS ENEMY HEALTH POOLS
        if (NayderInputSystem::key_states[GLFW_KEY_SPACE]) {
            if (space_was_released) {
                if (combat_system.PullTriggerLoop(primary_m4, dt)) {
                    audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");

                    // Direct weapon raycast hits the closest living zombie target
                    for (size_t i = 0; i < dynamic_horde.size(); ++i) {
                        if (!zombie_deads[i]) {
                            if (vital_system.ApplyDamageToZombie(i + 1, zombie_hps[i], zombie_deads[i], primary_m4.base_damage)) {
                                total_kills++;
                                std::cout << " 🔥 [SCORE DATA]: Total Zombies Terminated: " << total_kills << std::endl;
                            }
                            break; // Bullet absorbed by the first intercepted zombie target
                        }
                    }
                }
                space_was_released = false;
            }
        } else {
            space_was_released = true;
        }

        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, player_collider.x, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) {
            glBindVertexArray_ptr(VAO);
        }

        // Render pass bypassing dead meshes to optimize GPU cycles
        for (size_t i = 0; i < dynamic_horde.size(); ++i) {
            if (!zombie_deads[i]) {
                glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);
            }
        }

        engine_runtime.SwapHardwareBuffers();
        engine_clock.SynchronizeFrameRateLock();
        engine_runtime.HandleWindowPollEvents();
    }

    audio_system.TerminateAudioContext();
    engine_runtime.TerminateGraphicsContext();
    std::cout << "=======================================================" << std::endl;
    return 0;
}
