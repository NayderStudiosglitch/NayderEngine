#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/ZombieAI.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include "WeaponSystem.cpp"
#include "HealthSystem.cpp"
#include <iostream>
#include <vector>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.1.6] - CENTRAL CROSSHAIR SYSTEM" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 COMBAT INTERFACE RECONSTRUCTION PROGRESS MAP:" << std::endl;
    std::cout << "  v0.1.4 Health System Engine     -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.5 HUD System Interface     -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.6 Central Crosshair Node   -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.1.7 Inventory System Core    -> \342\226\220 NEXT" << std::endl;
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
    NayderHUDRenderer hud_engine;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Central Crosshair v0.1.6")) {
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

    EntityHealthPool player_vitals = { "NAYDER_01", 100, 100, 75, 75, false };
    WeaponProfile primary_m4 = combat_system.EquipWeaponPreset(WeaponType::ASSAULT_RIFLE);

    std::vector<ZombieEntityNode> dynamic_horde;
    int zombie_hps[] = { 100, 100, 100 };
    bool zombie_deads[] = { false, false, false };
    dynamic_horde.push_back({ 1, "Runner_Alpha", 16.0f, 4.0f, 15 });
    dynamic_horde.push_back({ 2, "Brute_Heavy",  22.0f, 2.0f, 35 });
    dynamic_horde.push_back({ 3, "Runner_Beta",  28.0f, 3.5f, 15 });

    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    bool space_was_released = true;
    int total_kills = 0;

    std::cout << "\n🚀 [CROSSHAIR LOCK INITIALIZED]:" << std::endl;
    std::cout << " -> Launching unified runtime. Targeting node centered on display boundaries." << std::endl;

    // MASTER ENGINE RUNTIME TICK GAME LOOP
    while (!engine_runtime.ShouldWindowClose() && !player_vitals.is_dead) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // Locomotion
        float movement_force = 0.0f;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            movement_force = 4.0f * dt;
            player_collider.x += movement_force;
        }

        zombie_ai.ProcessHordePathfindingTick(dynamic_horde, player_collider.x, dt);

        for (size_t i = 0; i < dynamic_horde.size(); ++i) {
            if (zombie_deads[i]) continue;
            float distance = std::abs(dynamic_horde[i].pos_x - player_collider.x);
            if (distance <= 1.8f) {
                vital_system.ApplyDamageToPlayer(player_vitals, dynamic_horde[i].attack_damage);
            }
        }

        if (NayderInputSystem::key_states[GLFW_KEY_SPACE]) {
            if (space_was_released) {
                if (combat_system.PullTriggerLoop(primary_m4, dt)) {
                    audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");
                    for (size_t i = 0; i < dynamic_horde.size(); ++i) {
                        if (!zombie_deads[i]) {
                            if (vital_system.ApplyDamageToZombie(i + 1, zombie_hps[i], zombie_deads[i], primary_m4.base_damage)) {
                                total_kills++;
                            }
                            break;
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
        
        for (size_t i = 0; i < dynamic_horde.size(); ++i) {
            if (!zombie_deads[i]) { glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0); }
        }

        hud_engine.SetOrthographicProjection();
        
        HUDLiveStats overlay_packet;
        overlay_packet.current_hp = player_vitals.current_hp;
        overlay_packet.max_hp = player_vitals.max_hp;
        overlay_packet.current_armor = player_vitals.current_armor;
        overlay_packet.max_armor = player_vitals.max_armor;
        overlay_packet.clip_ammo = primary_m4.current_clip;
        overlay_packet.max_clip = primary_m4.clip_capacity;
        overlay_packet.reserve_ammo = primary_m4.reserve_ammo;
        overlay_packet.total_kills = total_kills;
        overlay_packet.current_fps = engine_clock.GetCurrentFPS();
        overlay_packet.objective = "Reach Extraction Point";

        hud_engine.RenderHUDDashboard(overlay_packet);
        hud_engine.RestorePerspectiveProjection();

        engine_runtime.SwapHardwareBuffers();
        engine_clock.SynchronizeFrameRateLock();
        engine_runtime.HandleWindowPollEvents();
    }

    audio_system.TerminateAudioContext();
    engine_runtime.TerminateGraphicsContext();
    std::cout << "=======================================================" << std::endl;
    return 0;
}
