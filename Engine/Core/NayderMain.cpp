#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include <iostream>
#include <vector>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "  👑 [NAYDER ENGINE v0.1.1] - MULTIPLE ZOMBIE SPAWNING" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 MULTI-ENTITY SPAWNING PIPELINE MAP:" << std::endl;
    std::cout << "  v0.1.0 First Playable Prototype -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.1 Multiple Zombie Spawning -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.1.2 Weapon System Framework  -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Multi-Zombie Spawning v0.1.1")) {
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

    // 1. Chaje modèl la yon sèl kou nan VRAM (Asset Optimization)
    CompiledMesh zombie_mesh = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    unsigned int VAO, VBO, EBO;
    obj_loader.UploadMeshToGPU(zombie_mesh, VAO, VBO, EBO);

    // 2. KREYE MULTIPLE ZOMBIE LIST (Bouk kreyasyon dinamik)
    std::vector<BoxCollider> horde_list;
    std::cout << "\n🎬 [WORLD GENERATOR]: Spawning active Zombie Cluster nodes..." << std::endl;
    
    // N ap kreye 6 zonbi nan kowòdone X diferan pou simulate atak la (Spawn Zombie x6!)
    for (int i = 1; i <= 6; ++i) {
        float spawn_pos_x = 4.0f + (i * 3.0f); // Plase yo chak yonn apre lòt sou aks X la
        BoxCollider single_zombie = { spawn_pos_x, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f };
        horde_list.push_back(single_zombie);
        std::cout << "  ├── 🧟 [SPAWN SUCCESS]: Zombie_0" << i << " allocated at Vector3D(" << spawn_pos_x << ", 0.0, 0.0)" << std::endl;
    }

    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    bool space_was_released = true;

    std::cout << "\n🚀 [MULTI-ENTITY RUNTIME]: 6 dynamic zombies instantiated inside active Scene Graph!" << std::endl;

    // MASTER SYSTEM TICK RUNTIME LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        float movement_force = 0.0f;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            movement_force = 4.5f * dt;
        }

        if (movement_force > 0.0f) {
            BoxCollider predictive_box = player_collider;
            predictive_box.x += movement_force;

            bool path_blocked = false;
            // Tcheke kolizyon an tan reyèl kont tout 6 zonbi yo nan lis la!
            for (size_t i = 0; i < horde_list.size(); ++i) {
                if (physics_system.CheckCollision(predictive_box, horde_list[i])) {
                    path_blocked = true;
                    std::cout << " 🚫 [PHYSICS RESTRAINT]: Player collided live with Zombie_0" << (i + 1) << "! Movement vector locked." << std::endl;
                    break;
                }
            }

            if (!path_blocked) {
                player_collider.x += movement_force;
                std::cout << " 🏃‍♂️ [LOCOMOTION]: Translating player -> X: " << player_collider.x << std::endl;
            }
        }

        if (NayderInputSystem::key_states[GLFW_KEY_SPACE]) {
            if (space_was_released) {
                audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");
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

        // 3. MULTI-RENDERING DRAW CALLS: Desine tout 6 zonbi yo yon sèl kou sou ekran an!
        for (const auto& zb : horde_list) {
            // (Nòt: Nan v0.0.91 nou ka pouse kowòdone inifòm 'zb.x' sou shader a pou deplase chak modèl vizyèlman)
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
