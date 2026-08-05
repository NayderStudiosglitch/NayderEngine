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
    std::cout << "     [NEON FALL 17 v0.4.0] - DYNAMIC WAVE MODE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PRODUCTION GAMEPLAY PROGRESS MAP:" << std::endl;
    std::cout << "  v0.2.0 Neon Fall 17 Alpha Build -> \342\234\205 COMPLETE" << std::endl;
    std::cout << "  v0.3.0 Multiplayer Lobby Core   -> \342\234\205 COMPLETE" << std::endl;
    std::cout << "  v0.4.0 Zombie Wave Mode Logic   -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.5.0 Full Playtest Build Core -> \342\226\220 NEXT TARGET" << std::endl;
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
    NayderWaveDirector game_director;
    NayderHUDRenderer hud_engine;
    CollisionSystem physics_system;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Hardcore Wave Mode v0.4.0")) {
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
    
    WaveConfig current_session_waves = { 0, 0, 0, false, 0.0f };
    BarricadeNode sandbag_gate = { "Choke_Point_Sandbags", 6.0f, 150, 150, false };

    std::vector<ZombieEntityNode> dynamic_horde;
    game_director.InitializeNewWave(current_session_waves, dynamic_horde);

    BoxCollider player_collider = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};
    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    bool space_was_released = true;
    int current_wave_kills = 0;

    std::cout << "\n🎮 [WAVE SIMULATOR DEPLOYED] -> CHOKE POINT DEFENSE COMMENCING!" << std::endl;

    while (!engine_runtime.ShouldWindowClose() && !player_vitals.is_dead) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        if (!current_session_waves.wave_in_progress) {
            current_session_waves.next_wave_cooldown -= dt;
            if (current_session_waves.next_wave_cooldown <= 0.0f) {
                current_wave_kills = 0;
                game_director.InitializeNewWave(current_session_waves, dynamic_horde);
            }
        }

        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            player_collider.x += 4.5f * dt;
        }

        if (current_session_waves.wave_in_progress) {
            zombie_ai.ProcessHordePathfindingTick(dynamic_horde, player_collider.x, dt);
            
            for (size_t i = 0; i < dynamic_horde.size(); ++i) {
                if (!sandbag_gate.is_destroyed) {
                    game_director.EvaluateBarricadeIntersections(sandbag_gate, dynamic_horde[i].pos_x, dynamic_horde[i].attack_damage, dt);
                    if (dynamic_horde[i].pos_x <= sandbag_gate.pos_x + 1.0f) {
                        dynamic_horde[i].pos_x = sandbag_gate.pos_x + 1.0f;
                    }
                }
                
                if (sandbag_gate.is_destroyed) {
                    float dist = std::abs(dynamic_horde[i].pos_x - player_collider.x);
                    if (dist <= 1.8f) {
                        vital_system.ApplyDamageToPlayer(player_vitals, dynamic_horde[i].attack_damage);
                    }
                }
            }
        }

        if (NayderInputSystem::key_states[GLFW_KEY_SPACE] && current_session_waves.wave_in_progress) {
            if (space_was_released) {
                if (combat_system.PullTriggerLoop(primary_m4, dt)) {
                    audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");
                    current_wave_kills++;
                    std::cout << " 🎯 [COMBAT RECORD]: Kill Progress: " << current_wave_kills << " / " << current_session_waves.total_zombies_this_wave << std::endl;
                    game_director.EvaluateWaveVictoryConditions(current_session_waves, current_wave_kills);
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
        
        if (current_session_waves.wave_in_progress) {
            for (size_t i = 0; i < dynamic_horde.size(); ++i) {
                glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);
            }
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
        overlay_packet.total_kills = current_wave_kills;
        overlay_packet.current_fps = engine_clock.GetCurrentFPS();
        
        if (!current_session_waves.wave_in_progress) {
            overlay_packet.objective = "NEXT WAVE INCOMING IN: " + std::to_string(static_cast<int>(current_session_waves.next_wave_cooldown)) + "s";
        } else {
            overlay_packet.objective = "WAVE " + std::to_string(current_session_waves.current_wave) + " │ BARRICADE: " + (sandbag_gate.is_destroyed ? "BREACHED" : std::to_string(sandbag_gate.current_durability) + " HP");
        }

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
