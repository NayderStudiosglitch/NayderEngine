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
#include "Inventory.cpp"
#include "SaveLoadCore.cpp"
#include "MainMenu.cpp" // Interlocking real menu components modularly
#include "HealthSystem.cpp"
#include <iostream>
#include <vector>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.1.9] - INTERACTIVE MAIN MENU" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 GRAND SLAM MILESTONE COMPILATION STATUS:" << std::endl;
    std::cout << "  v0.1.7 Inventory System Core    -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.8 Save / Load State Sync   -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.9 Interactive Main Menu    -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << " 👑 v0.2.0 NEON FALL 17 ALPHA     -> \342\226\220 NEXT TARGET" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    NayderZombieAIEngine zombie_ai;
    NayderWeaponSystem combat_system;
    NayderInventoryEngine pack_system;
    NayderSaveLoadSystem save_system;
    NayderHealthSystem vital_system;
    NayderHUDRenderer hud_engine;
    NayderMainMenuEngine menu_system;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Interactive Menu v0.1.9")) {
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

    pack_system.InitializeDefaultSlots(combat_system);
    EntityHealthPool player_vitals = { "NAYDER_01", 100, 100, 75, 75, false };
    GameSaveStateNode loaded_session;
    
    std::vector<ZombieEntityNode> dynamic_horde;
    dynamic_horde.push_back({ 1, "Runner_Alpha", 16.0f, 4.0f, 15 });
    
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    // INITIALIZE GLOBAL ENGINE STATE TO THE FRONTEND LAYER
    EngineSystemState engine_state = EngineSystemState::FRONTEND_MENU;
    bool simulation_save_loaded = false;

    // 1. RUN THE FRONTEND CANVAS MENU SCREEN FIRST INTERACTIVELY
    engine_clock.TickClockStart();
    menu_system.RenderFrontendCanvas(107);
    
    char user_input_choice;
    std::cin >> user_input_choice;
    engine_state = menu_system.EvaluateSelectionInput(user_input_choice);

    if (user_input_choice == '2') {
        if (save_system.DeserializeSessionFromDisk(loaded_session)) {
            player_vitals.current_hp = loaded_session.player_hp;
            player_vitals.current_armor = loaded_session.player_armor;
            simulation_save_loaded = true;
        }
    }
    else if (user_input_choice == '3') {
        glfwSetWindowShouldClose(active_window, GLFW_TRUE);
    }

    std::cout << "\n🎬 [LAUNCHING CHOSEN VIEWPORT TARGET]: Sync done. Running loops." << std::endl;

    // MASTER ENGINE RUNTIME TICK GAME LOOP
    while (!engine_runtime.ShouldWindowClose() && engine_state == EngineSystemState::RUNTIME_GAMEPLAY) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // Runtime graphics loop clears
        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, 0.0f, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        // Render pass 2: 2D HUD Overlays
        hud_engine.SetOrthographicProjection();
        
        HUDLiveStats overlay_packet;
        overlay_packet.current_hp = player_vitals.current_hp;
        overlay_packet.max_hp = player_vitals.max_hp;
        overlay_packet.current_armor = player_vitals.current_armor;
        overlay_packet.max_armor = player_vitals.max_armor;
        overlay_packet.clip_ammo = 30;
        overlay_packet.max_clip = 30;
        overlay_packet.reserve_ammo = 180;
        overlay_packet.total_kills = simulation_save_loaded ? loaded_session.total_zombies_killed : 0;
        overlay_packet.current_fps = engine_clock.GetCurrentFPS();
        overlay_packet.objective = simulation_save_loaded ? "Resumed Map: " + loaded_session.active_world_map : "Mission Start: Survive the Zone";

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
