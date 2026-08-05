#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/ZombieAI.cpp"
#include "../Network/MultiplayerLobby.cpp" // Interlocking real lobby management layers modularly
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
    std::cout << "     [NEON FALL 17 v0.3.0] - MULTIPLAYER LOBBY RUNTIME" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 NETWORK PRODUCTION MARKS ONLINE:" << std::endl;
    std::cout << "  v0.2.0 Neon Fall 17 Alpha Build -> \342\234\205 COMPLETE" << std::endl;
    std::cout << "  v0.3.0 Multiplayer Lobby Core   -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.4.0 Zombie Wave Mode Logic   -> \342\226\220 NEXT" << std::endl;
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
    NayderMultiplayerLobby server_lobby;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Multiplayer Matchmaking v0.3.0")) {
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

    // =============================================================================
    // 🌐 LOBBY GOAL 1 & 2: JOIN SERVER MATCHMAKING ROOMS
    // =============================================================================
    std::cout << "\n🌐 [SERVER INITIALIZER]: Booting matchmaking socket adapters..." << std::endl;
    int p1_id = server_lobby.ProcessClientJoinRequest("NAYDER_01"); // Host local node
    int p2_id = server_lobby.ProcessClientJoinRequest("CLAN_MEMBER_02");
    int p3_id = server_lobby.ProcessClientJoinRequest("CLAN_BRO_03");

    // =============================================================================
    // 🛡️ LOBBY GOAL 3: JOIN TEAM VECTOR REPLICATION SLOTS
    // =============================================================================
    server_lobby.AssignPlayerToTacticalTeam(p1_id, TeamTeam::SQUAD_ALPHA);
    server_lobby.AssignPlayerToTacticalTeam(p2_id, TeamTeam::SQUAD_ALPHA);
    server_lobby.AssignPlayerToTacticalTeam(p3_id, TeamTeam::SQUAD_BRAVO);

    EntityHealthPool player_vitals = { "NAYDER_01", 100, 100, 75, 75, false };
    WeaponProfile primary_m4 = combat_system.EquipWeaponPreset(WeaponType::ASSAULT_RIFLE);

    std::vector<ZombieEntityNode> dynamic_horde;
    dynamic_horde.push_back({ 1, "Zombie_Runner", 14.0f, 4.0f, 25 }); // Set up single runner for proxy tests

    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    bool space_was_released = true;
    int total_kills_score = 0;

    std::cout << "\n🎮 [LOBBY HANDSHAKES SYNCHRONIZED] -> MATCH STARTING NOW!" << std::endl;

    // MASTER ENGINE RUNTIME TICK GAME LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // Fetch local client data from our lobby registry loops to update respawn clocks
        auto& clients = server_lobby.GetLobbyClientsPool();

        // -----------------------------------------------------------------
        // ⏳ LOBBY GOAL 4: CONDITION ALARM AND PLAYER RESPAWN SYSTEM SCRIPT
        // -----------------------------------------------------------------
        if (player_vitals.is_dead) {
            if (clients[0].net_state != ConnectionState::SPECTATING_DEAD) {
                clients[0].net_state = ConnectionState::SPECTATING_DEAD;
                clients[0].respawn_timer = 5.0f; // 5-Second tactical respawn window penalty loop
            }
            
            // Run system clock countdown tick
            server_lobby.ProcessRespawnTimerTicks(clients[0], dt, player_collider.x);
            
            if (clients[0].net_state == ConnectionState::IN_MATCH) {
                // Restore vital pools completely when respawn clock clears
                player_vitals.current_hp = 100;
                player_vitals.current_armor = 75;
                player_vitals.is_dead = false;
            }
        }

        // Only allow positional matrix translation if the player is alive inside the match session
        if (!player_vitals.is_dead) {
            if (NayderInputSystem::key_states[GLFW_KEY_W]) {
                player_collider.x += 4.5f * dt;
            }

            // Pathfinding processing vectors
            zombie_ai.ProcessHordePathfindingTick(dynamic_horde, player_collider.x, dt);

            // Proximity threat evaluations
            float distance = std::abs(dynamic_horde[0].pos_x - player_collider.x);
            if (distance <= 1.8f) {
                vital_system.ApplyDamageToPlayer(player_vitals, dynamic_horde[0].attack_damage);
            }

            // Weapon triggers
            if (NayderInputSystem::key_states[GLFW_KEY_SPACE]) {
                if (space_was_released) {
                    if (combat_system.PullTriggerLoop(primary_m4, dt)) {
                        audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");
                        if (std::abs(dynamic_horde[0].pos_x - player_collider.x) < 25.0f) {
                            total_kills_score++;
                            dynamic_horde[0].pos_x = player_collider.x + 20.0f; // Force push respawn coordinate on zombie node
                        }
                    }
                    space_was_released = false;
                }
            } else {
                space_was_released = true;
            }
        }

        // Frame rendering submissions
        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, player_collider.x, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        // Render pass 2: HUD Dashboard
        hud_engine.SetOrthographicProjection();
        
        HUDLiveStats overlay_packet;
        overlay_packet.current_hp = player_vitals.current_hp;
        overlay_packet.max_hp = player_vitals.max_hp;
        overlay_packet.current_armor = player_vitals.current_armor;
        overlay_packet.max_armor = player_vitals.max_armor;
        overlay_packet.clip_ammo = primary_m4.current_clip;
        overlay_packet.max_clip = primary_m4.clip_capacity;
        overlay_packet.reserve_ammo = primary_m4.reserve_ammo;
        overlay_packet.total_kills = total_kills_score;
        overlay_packet.current_fps = engine_clock.GetCurrentFPS();
        
        // Print active squad configuration label onto screen overlays!
        overlay_packet.objective = (player_vitals.is_dead) ? "RESPAWNING IN COOLDOWN..." : "TEAM: SQUAD_ALPHA │ SECTOR: CITY";

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
