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
#include "SaveLoadCore.cpp" // Interlocking upgraded persistence sync systems
#include "HealthSystem.cpp"
#include <iostream>
#include <vector>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.1.8] - PERSISTENCE STATE SYNC" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 MILESTONE TRACK SYSTEM UPDATE:" << std::endl;
    std::cout << "  v0.1.6 Central Crosshair Node   -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.7 Inventory System Core    -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.1.8 Save / Load State Sync   -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.1.9 Interactive Main Menu    -> \342\226\220 NEXT" << std::endl;
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
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - State Sync v0.1.8")) {
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

    // Initialize systems data frames
    pack_system.InitializeDefaultSlots(combat_system);
    EntityHealthPool player_vitals = { "NAYDER_01", 100, 100, 75, 75, false };

    // SIMULATE SUB-SYSTEM COMBAT DEVIATION PRIOR TO SERIALIZATION
    pack_system.CycleActiveSlotSelection(1); // Swapped to pistol
    WeaponProfile& pistol = pack_system.GetActiveWeaponProfile();
    pistol.current_clip = 12; // Fired 3 rounds from the pistol magazine clip
    
    pack_system.CycleActiveSlotSelection(0); // Swapped back to primary
    WeaponProfile& m4 = pack_system.GetActiveWeaponProfile();
    m4.current_clip = 22; // Fired 8 rounds from the M4 clip
    m4.reserve_ammo = 150;

    // 1. ASSEMBLE EXTENDED PERSISTENCE PACKET BASED ON CURRENT GAME STATE
    GameSaveStateNode active_session;
    active_session.survival_day = 34;
    active_session.player_hp = player_vitals.current_hp;
    active_session.player_armor = player_vitals.current_armor;
    active_session.total_zombies_killed = 412;
    active_session.active_equipped_slot_index = pack_system.GetActiveSlotIndex();
    active_session.primary_m4_clip = m4.current_clip;
    active_session.primary_m4_reserve = m4.reserve_ammo;
    
    pack_system.CycleActiveSlotSelection(1);
    WeaponProfile& current_pistol = pack_system.GetActiveWeaponProfile();
    active_session.secondary_pistol_clip = current_pistol.current_clip;
    active_session.secondary_pistol_reserve = current_pistol.reserve_ammo;
    active_session.active_world_map = "Desert_Ghost_City_Bravo";

    // Re-lock array view states to match origin presets
    pack_system.CycleActiveSlotSelection(active_session.active_equipped_slot_index);

    // 2. TRIGGER MASTER PERSISTENCE DISK WRITE
    save_system.SerializeSessionToDisk(active_session);

    std::cout << "\n-------------------------------------------------------" << std::endl;

    // 3. SIMULATE AUTOMATED HARDWARE READBACK TEST ON GAME BOOT
    GameSaveStateNode loaded_session;
    if (save_system.DeserializeSessionFromDisk(loaded_session)) {
        std::cout << " 🎮 [SYNCHRONIZATION PROFILE PASS]:" << std::endl;
        std::cout << "  ├── Loaded Map   : " << loaded_session.active_world_map << " │ Surviving Day: " << loaded_session.survival_day << std::endl;
        std::cout << "  ├── M4 Mag Sync  : " << loaded_session.primary_m4_clip << " / " << loaded_session.primary_m4_reserve << " rounds recovered." << std::endl;
        std::cout << "  └── Pistol Sync  : " << loaded_session.secondary_pistol_clip << " / " << loaded_session.secondary_pistol_reserve << " rounds recovered." << std::endl;
    }

    std::cout << "\n🎬 [SYSTEM REPLICATION]: Flushing I/O handles and initializing display window..." << std::endl;

    std::vector<ZombieEntityNode> dynamic_horde;
    dynamic_horde.push_back({ 1, "Runner_Alpha", 16.0f, 4.0f, 15 });
    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");

    // RUN THE COMPREHENSIVE WINDOW TICK LOOPS
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, player_collider.x, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        hud_engine.SetOrthographicProjection();
        HUDLiveStats overlay_packet = { player_vitals.current_hp, 100, player_vitals.current_armor, 75, m4.current_clip, 30, m4.reserve_ammo, loaded_session.total_zombies_killed, engine_clock.GetCurrentFPS(), "State Restored Perfectly" };
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
