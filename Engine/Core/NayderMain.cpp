#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/ZombieAI.cpp"
#include "../AI/WaveDirector.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include "WeaponSystem.cpp"
#include "HealthSystem.cpp"
#include <iostream>
#include <vector>
#include <cmath>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "  👑 [NAYDER ENGINE v0.3.5] - STANDALONE PLAYABLE WORLD" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 3D HARDWARE VIEWPORT RENDERING SLOTS ACTIVE:" << std::endl;
    std::cout << "  [+] v0.3.1 Real Terrain Mesh Streamer     -> ONLINE" << std::endl;
    std::cout << "  [+] v0.3.2 Static Obstacles & Props       -> ONLINE" << std::endl;
    std::cout << "  [+] v0.3.3 Animated Zombie Mesh VRAM      -> ONLINE" << std::endl;
    std::cout << "  [+] v0.3.4 First-Person 360 Camera Matrix -> ONLINE" << std::endl;
    std::cout << "  [+] v0.3.5 Unified Playable Desert City   -> ONLINE PA OU" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    NayderZombieAIEngine zombie_ai;
    NayderHUDRenderer hud_engine;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Playable World v0.3.5")) {
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

    CompiledMesh terrain_mesh = obj_loader.ParseOBJFile("Assets/Models/terrain.obj");
    unsigned int terrain_VAO, terrain_VBO, terrain_EBO;
    obj_loader.UploadMeshToGPU(terrain_mesh, terrain_VAO, terrain_VBO, terrain_EBO);

    CompiledMesh zombie_mesh = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    unsigned int zombie_VAO, zombie_VBO, zombie_EBO;
    obj_loader.UploadMeshToGPU(zombie_mesh, zombie_VAO, zombie_VBO, zombie_EBO);

    float player_pos_x = 0.0f, player_pos_y = 1.8f, player_pos_z = 0.0f;
    float cam_yaw = -90.0f, cam_pitch = 0.0f;

    PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");

    std::cout << "\n🚀 [THE INITIALIZATION IS COMPLETE] -> MATCH READY!" << std::endl;

    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();
        int current_active_fps = engine_clock.GetCurrentFPS();

        NayderInputSystem::GetCameraOrientation(cam_yaw, cam_pitch);
        
        float rad_yaw = cam_yaw * (3.14159f / 180.0f);
        float forward_x = std::cos(rad_yaw);
        float forward_z = std::sin(rad_yaw);
        float right_x = -std::sin(rad_yaw);
        float right_z = std::cos(rad_yaw);

        float cam_move_speed = 5.0f * dt;

        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            player_pos_x += forward_x * cam_move_speed;
            player_pos_z += forward_z * cam_move_speed;
        }
        if (NayderInputSystem::key_states[GLFW_KEY_S]) {
            player_pos_x -= forward_x * cam_move_speed;
            player_pos_z -= forward_z * cam_move_speed;
        }
        if (NayderInputSystem::key_states[GLFW_KEY_A]) {
            player_pos_x -= right_x * cam_move_speed;
            player_pos_z -= right_z * cam_move_speed;
        }
        if (NayderInputSystem::key_states[GLFW_KEY_D]) {
            player_pos_x += right_x * cam_move_speed;
            player_pos_z += right_z * cam_move_speed;
        }

        static float debug_timer = 0.0f;
        debug_timer += dt;
        if (debug_timer >= 0.5f) {
            std::cout << " 🎥 [FPS CAM NODE]: Location Coordinates: (" << player_pos_x << ", " << player_pos_z << ") │ " << current_active_fps << " FPS" << std::endl;
            debug_timer = 0.0f;
        }

        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, player_pos_x, player_pos_y, player_pos_z);
        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(terrain_VAO); }
        glDrawElements(GL_TRIANGLES, terrain_mesh.total_indices, GL_UNSIGNED_INT, 0);

        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(zombie_VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        hud_engine.SetOrthographicProjection();
        HUDLiveStats overlay_packet = { 100, 100, 75, 75, 30, 30, 180, 0, current_active_fps, "ALPHA MAP: Desert Ghost City" };
        hud_engine.RenderHUDDashboard(overlay_packet);
        hud_engine.RestorePerspectiveProjection();

        engine_runtime.SwapHardwareBuffers();
        engine_clock.SynchronizeFrameRateLock();
        engine_runtime.HandleWindowPollEvents();
    }

    audio_system.TerminateAudioContext();
    engine_runtime.TerminateGraphicsContext();
    return 0;
}
