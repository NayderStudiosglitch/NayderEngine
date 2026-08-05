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
    std::cout << "     [NEON FALL 17 v0.3.7] - INTERACTIVE USER HUD CORE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 GRAPHICAL INTERFACE PROGRESS MATRIX:" << std::endl;
    std::cout << "  [+] v0.3.5 Standalone 360 Perspective World -> COMPLETE" << std::endl;
    std::cout << "  [+] v0.3.6 Screen-Space Weapon Mesh Overlay -> COMPLETE" << std::endl;
    std::cout << "  [+] v0.3.7 Interactive User HUD/UI Matrix  -> ONLINE PA OU" << std::endl;
    std::cout << "  [+] v0.3.8 Real-Time Crosshair Hit Markers  -> ▐ NEXT" << std::endl;
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
    NayderWeaponSystem combat_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Graphical HUD v0.3.7")) {
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

    WeaponProfile primary_m4 = combat_system.EquipWeaponPreset(WeaponType::ASSAULT_RIFLE);

    // Initial playtest structural status markers
    int simulated_hp = 85;
    int simulated_armor = 40;

    float player_pos_x = 0.0f, player_pos_y = 1.8f, player_pos_z = 0.0f;
    float cam_yaw = -90.0f, cam_pitch = 0.0f;

    PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    bool mouse_left_released = true;

    std::cout << "\n🚀 [INTERACTIVE HUD RUNTIME ACTIVE]:" << std::endl;
    std::cout << " -> Press [SPACEBAR] to take damage and watch the green health bar shrink live on screen!" << std::endl;

    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();
        int active_fps = engine_clock.GetCurrentFPS();

        NayderInputSystem::GetCameraOrientation(cam_yaw, cam_pitch);
        
        float rad_yaw = cam_yaw * (3.14159f / 180.0f);
        float forward_x = std::cos(rad_yaw); float forward_z = std::sin(rad_yaw);
        float right_x = -std::sin(rad_yaw);  float right_z = std::cos(rad_yaw);

        float cam_move_speed = 5.0f * dt;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) { player_pos_x += forward_x * cam_move_speed; player_pos_z += forward_z * cam_move_speed; }
        if (NayderInputSystem::key_states[GLFW_KEY_S]) { player_pos_x -= forward_x * cam_move_speed; player_pos_z -= forward_z * cam_move_speed; }
        if (NayderInputSystem::key_states[GLFW_KEY_A]) { player_pos_x -= right_x * cam_move_speed; player_pos_z -= right_z * cam_move_speed; }
        if (NayderInputSystem::key_states[GLFW_KEY_D]) { player_pos_x += right_x * cam_move_speed; player_pos_z += right_z * cam_move_speed; }

        // Simulate taking dynamic hits when pressing SPACEBAR to test bar scaling attributes
        if (NayderInputSystem::key_states[GLFW_KEY_SPACE]) {
            if (simulated_hp > 10) simulated_hp -= 1; // Deduct HP live
        }

        int left_mouse_click = glfwGetMouseButton(active_window, GLFW_MOUSE_BUTTON_LEFT);
        if (left_mouse_click == GLFW_PRESS) {
            if (mouse_left_released) {
                if (combat_system.PullTriggerLoop(primary_m4, dt)) {
                    audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");
                }
                mouse_left_released = false;
            }
        } else {
            mouse_left_released = true;
        }

        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        // 3D Scene drawing pass
        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, player_pos_x, player_pos_y, player_pos_z);
        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(terrain_VAO); }
        glDrawElements(GL_TRIANGLES, terrain_mesh.total_indices, GL_UNSIGNED_INT, 0);

        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(zombie_VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        // =============================================================================
        // 🎛️ SUBMIT PURE OPENGL GRAPHICAL HUD OVERLAYS RASTERIZATION
        // =============================================================================
        hud_engine.SetOrthographicProjection();
        
        HUDLiveStats overlay_packet;
        overlay_packet.current_hp = simulated_hp;     // Pipe dynamic data markers
        overlay_packet.max_hp = 100;
        overlay_packet.current_armor = simulated_armor;
        overlay_packet.max_armor = 75;
        overlay_packet.clip_ammo = primary_m4.current_clip;
        overlay_packet.max_clip = primary_m4.clip_capacity;
        overlay_packet.reserve_ammo = primary_m4.reserve_ammo;
        overlay_packet.total_kills = 0;
        overlay_packet.current_fps = active_fps;
        overlay_packet.objective = "RASTERiZER INTERACTiVE ENGiNE";

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
