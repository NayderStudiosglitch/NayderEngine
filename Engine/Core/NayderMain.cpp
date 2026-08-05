#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Editor/EditorWorkspace.cpp"
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/ZombieAI.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include "WeaponSystem.cpp"
#include "HealthSystem.cpp"
#include <iostream>
#include <vector>

bool ProcessMousePickingRaycast(double mouse_x, double mouse_y, float zombie_x, float zombie_z, float radius);

enum class WorkspaceState { EDITOR_EDITING, GAME_PLAYMODE };

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.2.3] - INTEGRATED PLAY MODE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 RECONSTRUCTION RUNTIME PROGRESS MAP:" << std::endl;
    std::cout << "  v0.2.1 Object Selection & Gizmos -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.2.2 Live Mouse Picking Matrix -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.2.3 Real-Time Play Mode Loop  -> \342\234\205 OPERATIONAL PA OU" << std::endl;
    std::cout << "  v0.3.0 Full Production Editor   -> \342\226\220 NEXT TARGET" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    NayderEditorWorkspace editor_suite;
    NayderZombieAIEngine zombie_ai;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 Workspace Editor v0.2.3")) {
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

    // Initial asset profiles
    SelectedEntityData zombie_data = { "None", 16.5f, 0.0f, -2.4f, 0.0f, 45.0f, 0.0f, 1.2f, "zombie.obj" };
    SelectedEntityData backup_cache = zombie_data; // State Cache for hot-returns
    
    std::vector<ZombieEntityNode> dynamic_horde;
    dynamic_horde.push_back({ 1, "PlayMode_Runner", zombie_data.pos_x, 4.0f, 15 });

    WorkspaceState current_state = WorkspaceState::EDITOR_EDITING;
    bool mouse_button_released = true;
    bool p_key_released = true;

    std::cout << "\n🚀 [PLAY MODE PIPELINE CONFIGURED]:" << std::endl;
    std::cout << " -> In Edit Mode  : Left Click to select objects. Tap [P] to launch Play Mode!" << std::endl;
    std::cout << " -> In Play Mode  : Move mouse for 360 look. Tap [ESCAPE] to hot-return to Editor!" << std::endl;

    // MASTER ENGINE RUNTIME TICK WORKSPACE LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // 1. MONITOR OS INTERRUPT TO TOGGLE INTO PLAY MODE (Key: P)
        if (NayderInputSystem::key_states[GLFW_KEY_P]) {
            if (p_key_released && current_state == WorkspaceState::EDITOR_EDITING) {
                backup_cache = zombie_data; // Cache editor layout values
                current_state = WorkspaceState::GAME_PLAYMODE;
                glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock mouse for FPS control
                std::cout << "\n▶️  [PLAY MODE TRIGGERED]: Simulation unchained! Core AI and physics components awake." << std::endl;
                p_key_released = false;
            }
        } else { p_key_released = true; }

        // 2. MONITOR ESCAPE KEY TO COLD-SNAP BACK TO EDITOR
        if (NayderInputSystem::key_states[GLFW_KEY_ESCAPE] && current_state == WorkspaceState::GAME_PLAYMODE) {
            zombie_data = backup_cache; // Restore editor layout values instantly (0% leakage)
            current_state = WorkspaceState::EDITOR_EDITING;
            glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Free cursor back to panels
            std::cout << "\n⏸️  [PLAY MODE TERMINATED]: Reverted workspace nodes back to cached editor values safely." << std::endl;
        }

        // =============================================================================
        // BRANCH EXECUTION STATE MACHINE FORK
        // =============================================================================
        if (current_state == WorkspaceState::EDITOR_EDITING) {
            // EDITING INTERRUPTS: Mouse selection logic checks
            int mouse_state = glfwGetMouseButton(active_window, GLFW_MOUSE_BUTTON_LEFT);
            if (mouse_state == GLFW_PRESS) {
                if (mouse_button_released) {
                    double xpos, ypos;
                    glfwGetCursorPos(active_window, &xpos, &ypos);
                    if (ProcessMousePickingRaycast(xpos, ypos, zombie_data.pos_x, zombie_data.pos_z, 1.2f)) {
                        zombie_data.name = "Zombie_01";
                    } else { zombie_data.name = "None"; }
                    mouse_button_released = false;
                }
            } else { mouse_button_released = true; }
        } 
        else if (current_state == WorkspaceState::GAME_PLAYMODE) {
            // PLAYMODE INTERRUPTS: Active live simulations!
            // Automatically process active multi-agent AI pathfinding tracks
            dynamic_horde[0].pos_x = zombie_data.pos_x;
            zombie_ai.ProcessHordePathfindingTick(dynamic_horde, 0.0f, dt); // Simulate player standing at origin
            zombie_data.pos_x = dynamic_horde[0].pos_x; // Feed AI adjustments straight to display registers
        }

        // Hardware drawing passes
        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, 0.0f, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        // UI Panel Drawing Passes
        editor_suite.SetEditorLayoutMatrix();
        editor_suite.DrawSceneHierarchyPanel();
        editor_suite.DrawCentralViewportPanel();
        
        // Pass specialized status tokens to update inspector flags based on current execution mode
        if (current_state == WorkspaceState::GAME_PLAYMODE) {
            zombie_data.mesh_source = "PLAY_MODE_ACTIVE";
        } else {
            zombie_data.mesh_source = "zombie.obj";
        }
        editor_suite.DrawInspectorPanel(zombie_data);
        
        editor_suite.DrawContentBrowserPanel();

        engine_runtime.SwapHardwareBuffers();
        engine_clock.SynchronizeFrameRateLock();
        engine_runtime.HandleWindowPollEvents();
    }

    audio_system.TerminateAudioContext();
    engine_runtime.TerminateGraphicsContext();
    return 0;
}
