#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/ZombieAI.cpp" // Interlocking real multi-agent pathfinding components
#include "Input.cpp"
#include "GameLoop.cpp"
#include "WeaponSystem.cpp"
#include <iostream>
#include <vector>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.1.3] - MULTI-AGENT AI PATHFINDING" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 ROADMAP STATUS MATRIX COMPILING:" << std::endl;
    std::cout << "  v0.1.1 Multiple Zombie Spawning -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.2 Weapon System Framework  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.3 Zombie AI Pathing Mesh   -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.1.4 Health System Engine     -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    NayderZombieAIEngine zombie_ai;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Zombie AI Pathfinding v0.1.3")) {
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

    // 1. SPAWN HIGH-PERFORMANCE INTELiGENT MULTIPLE ZOMBIES WITH CUSTOM TYPE MULTIPLIERS
    std::vector<ZombieEntityNode> dynamic_horde;
    std::cout << "\n🎬 [WORLD ENTIY GENERATOR]: Allocating polymorphic AI tracking nodes..." << std::endl;
    
    // Spawning 3 customized polymorphic zombies further down the road vector
    dynamic_horde.push_back({ 1, "Runner_Alpha", 15.0f, 5.5f, 15 }); // Ultra fast speed (5.5 m/s)
    dynamic_horde.push_back({ 2, "Brute_Lou",   22.0f, 2.2f, 45 }); // Slower speed (2.2 m/s) but heavy damage!
    dynamic_horde.push_back({ 3, "Runner_Beta",  28.0f, 4.8f, 15 });

    std::cout << "  ├── ✅ Spawning complete! 3 pathfinding entities linked into active tracking matrix." << std::endl;

    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    bool space_was_released = true;

    std::cout << "\n🚀 [AI ENGINE PIPELINE UNLOCKED]:" << std::endl;
    std::cout << " -> HOLD [W] to move player forward." << std::endl;
    std::cout << " -> Watch the console log: The zombies will actively run toward your position coordinates!" << std::endl;

    // MASTER ENGINE RUNTIME TICK GAME LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // Player Locomotion
        float movement_force = 0.0f;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            movement_force = 4.0f * dt;
            player_collider.x += movement_force;
            std::cout << "\n👤 [PLAYER MOVED]: Location X updated to: " << player_collider.x << std::endl;
        }

        // 2. EXECUTE REAL-TIME LIVE MULTI-AGENT AI PATHFINDING TICK!
        zombie_ai.ProcessHordePathfindingTick(dynamic_horde, player_collider.x, dt);

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

        // Render loop tracing the updated vector slots
        for (const auto& zb : dynamic_horde) {
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
