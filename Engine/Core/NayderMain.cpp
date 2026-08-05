#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include "WeaponSystem.cpp" // Interlocking real weapon components modularly
#include <iostream>
#include <vector>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.1.2] - INTEGRATED WEAPON CORE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 COMBAT LOGIC INTEGRATION PROGRESS MAP:" << std::endl;
    std::cout << "  v0.1.0 First Playable Prototype -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.1 Multiple Zombie Spawning -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.2 Weapon System Framework  -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.1.3 Zombie AI Pathing Mesh   -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderWeaponSystem combat_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Weapon System Profile v0.1.2")) {
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

    // 1. INITIALIZE LOADOUT ASSETS VIA COMPONENT CORES
    WeaponProfile primary_m4 = combat_system.EquipWeaponPreset(WeaponType::ASSAULT_RIFLE);

    std::vector<BoxCollider> horde_list;
    for (int i = 1; i <= 3; ++i) {
        horde_list.push_back({ 5.0f + (i * 4.0f), 0.0f, 0.0f, 1.0f, 2.0f, 1.0f });
    }

    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    bool space_was_released = true;
    bool r_was_released = true;

    std::cout << "\n🚀 [WEAPON RUNTIME INITIALIZED]:" << std::endl;
    std::cout << " -> HOLD [W] to move forward." << std::endl;
    std::cout << " -> HOLD [SPACEBAR] to continuous fire automatic rifle clip loops." << std::endl;
    std::cout << " -> TAP [R] to manually reload the active magazine feed." << std::endl;
    std::cout << " -> Press [ESCAPE] on your keyboard to stop the process securely." << std::endl;

    // MASTER ENGINE RUNTIME TICK GAME LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // Locomotion tracks
        float movement_force = 0.0f;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            movement_force = 4.5f * dt;
        }
        if (movement_force > 0.0f) {
            BoxCollider predictive_box = player_collider;
            predictive_box.x += movement_force;
            bool path_blocked = false;
            for (const auto& zb : horde_list) {
                if (physics_system.CheckCollision(predictive_box, zb)) { path_blocked = true; break; }
            }
            if (!path_blocked) player_collider.x += movement_force;
        }

        // 2. HARDWARE TRIGGER BINDINGS & CLOCK RATIO SYNCS
        if (NayderInputSystem::key_states[GLFW_KEY_SPACE]) {
            // Automatic structural fire loops linked natively to your custom sound streams
            if (space_was_released) {
                if (combat_system.PullTriggerLoop(primary_m4, dt)) {
                    audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");
                }
                space_was_released = false; // Simulated lock based on single framework calls
            }
        } else {
            space_was_released = true;
        }

        // 3. RELOAD MECHANICS BINDING (Key: R)
        if (NayderInputSystem::key_states[GLFW_KEY_R]) {
            if (r_was_released) {
                combat_system.ExecuteReloadSequence(primary_m4);
                r_was_released = false;
            }
        } else {
            r_was_released = true;
        }

        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, player_collider.x, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) {
            glBindVertexArray_ptr(VAO);
        }

        for (const auto& zb : horde_list) {
            glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);
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
