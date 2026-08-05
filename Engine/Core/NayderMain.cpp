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

// Link the universal multi-object raycast selection handler
int EvaluateUniversalScenePicking(double mouse_x, double mouse_y, const std::vector<SelectedEntityData>& scene_graph);

enum class EditorStateFork { DEV_EDITING, SIM_PLAYMODE };

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.3.0] - FULL WORKSPACE EDITOR" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 100%% CORE INTERFACE INTEGRATION ROADMAP UNLOCKED:" << std::endl;
    std::cout << "  v0.2.1 Object Selection & Gizmos -> \342\234\205 COMPLETE" << std::endl;
    std::cout << "  v0.2.2 Live Mouse Picking Matrix -> \342\234\205 COMPLETE" << std::endl;
    std::cout << "  v0.2.3 Real-Time Play Mode Loop  -> \342\234\205 COMPLETE" << std::endl;
    std::cout << "  v0.3.0 Full Production Editor   -> \342\234\205 ONLINE PA OU" << std::endl;
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

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Nayder Engine v0.3.0 - Full Production Editor")) {
        return -1;
    }

    GLFWwindow* active_window = glfwGetCurrentContext();
    input_engine.ConfigureInputCallbacks(active_window);
    
    // Release the mouse hardware lock completely so it functions as a desktop application tool
    glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
    // 📦 WORKSPACE GOAL: DYNAMIC SCENE GRAPH DATABASE ACCUMULATOR
    // =============================================================================
    std::vector<SelectedEntityData> master_scene_graph;
    master_scene_graph.push_back({ "Player_Spawn_Node", 0.0f,  1.8f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f, "soldier.obj" });
    master_scene_graph.push_back({ "Zombie_Runner_01",  12.5f, 0.0f, -4.2f, 0.0f, 90.0f, 0.0f, 1.2f, "zombie.obj" });
    master_scene_graph.push_back({ "Zombie_Brute_02",   19.0f, 0.0f, -8.0f, 0.0f, 45.0f, 0.0f, 2.0f, "zombie.obj" });
    master_scene_graph.push_back({ "Abandoned_House",   -8.0f, 0.0f, 15.0f, 0.0f, 0.0f,  0.0f, 1.0f, "house.obj" });

    // Instantiating a proxy default selection state node structure
    SelectedEntityData current_focused_node = { "None", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, "None" };
    int active_selected_index = -1;

    std::vector<ZombieEntityNode> playmode_ai_pool;
    playmode_ai_pool.push_back({ 1, "Editor_Runner", 12.5f, 4.0f, 15 });

    EditorStateFork current_editor_loop_mode = EditorStateFork::DEV_EDITING;
    bool mouse_click_released = true;
    bool p_key_released = true;

    std::cout << "\n🚀 [FULL PRODUCTION WORKSPACE ACTIVE]:" << std::endl;
    std::cout << " -> LEFT CLICK anywhere across the viewport to universally select and inspect ANY scene node!" << std::endl;
    std::cout << " -> Tap [P] to launch simulation Play Mode │ Tap [ESCAPE] to hot-return to tool panels." << std::endl;

    // MASTER ENGINE RUNTIME TICK WORKSPACE LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // 1. MONITOR PLAY MODE TOGGLE SHORTCUT INTERRUPTS (Key: P)
        if (NayderInputSystem::key_states[GLFW_KEY_P]) {
            if (p_key_released && current_editor_loop_mode == EditorStateFork::DEV_EDITING) {
                current_editor_loop_mode = EditorStateFork::SIM_PLAYMODE;
                glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Claim cursor for combat gameplay
                std::cout << "\n▶️  [PLAY MODE TRIGGERED]: Simulation active! Processing live delta AI pathing streams." << std::endl;
                p_key_released = false;
            }
        } else { p_key_released = true; }

        if (NayderInputSystem::key_states[GLFW_KEY_ESCAPE] && current_editor_loop_mode == EditorStateFork::SIM_PLAYMODE) {
            current_editor_loop_mode = EditorStateFork::DEV_EDITING;
            glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Return mouse control back to editing sliders
            std::cout << "\n⏸️  [PLAY MODE TERMINATED]: Simulation frozen. Tool panels active." << std::endl;
        }

        // =============================================================================
        // CONTEXT STATE MACHINE FORK LOOPS
        // =============================================================================
        if (current_editor_loop_mode == EditorStateFork::DEV_EDITING) {
            // 2. PROCESS UNIVERSAL 3D MOUSE PICKING MATRIX ACCROSS ALL SCENE NODES
            int mouse_left_button = glfwGetMouseButton(active_window, GLFW_MOUSE_BUTTON_LEFT);
            if (mouse_left_button == GLFW_PRESS) {
                if (mouse_click_released) {
                    double mx, my;
                    glfwGetCursorPos(active_window, &mx, &my);
                    
                    // Run unified raycast query calculations down the scene vector arrays
                    active_selected_index = EvaluateUniversalScenePicking(mx, my, master_scene_graph);
                    
                    if (active_selected_index != -1) {
                        current_focused_node = master_scene_graph[active_selected_index]; // Expose variables to Inspector!
                    } else {
                        current_focused_node = { "None", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, "None" };
                    }
                    mouse_click_released = false;
                }
            } else { mouse_click_released = true; }

            // Scaling transform handles using WASD keyboard shifts if a prop is actively focused
            if (active_selected_index != -1 && NayderInputSystem::key_states[GLFW_KEY_W]) {
                master_scene_graph[active_selected_index].pos_x += 3.0f * dt;
                current_focused_node = master_scene_graph[active_selected_index]; // Update inspector live
            }
        } 
        else if (current_editor_loop_mode == EditorStateFork::SIM_PLAYMODE) {
            // PlayMode loops: unchaining polymorphic AI movement scripts
            zombie_ai.ProcessHordePathfindingTick(playmode_ai_pool, 0.0f, dt);
            if (active_selected_index == 1) { // If Zombie_01 was active, trace its live running steps
                master_scene_graph[1].pos_x = playmode_ai_pool[0].pos_x;
                current_focused_node = master_scene_graph[1];
            }
        }

        // Hardware hardware render passes
        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, 0.0f, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        // Compile and print the complete multi-panel Application IDE layout overlay!
        editor_suite.SetEditorLayoutMatrix();
        editor_suite.DrawSceneHierarchyPanel();
        editor_suite.DrawCentralViewportPanel();
        
        // Feed live state tokens to correctly flag inspector panels based on loop modes
        if (current_editor_loop_mode == EditorStateFork::SIM_PLAYMODE) {
            current_focused_node.mesh_source = "PLAY_MODE_ACTIVE";
        } else if (active_selected_index != -1) {
            current_focused_node.mesh_source = master_scene_graph[active_selected_index].mesh_source;
        }
        editor_suite.DrawInspectorPanel(current_focused_node);
        
        editor_suite.DrawContentBrowserPanel();

        engine_runtime.SwapHardwareBuffers();
        engine_clock.SynchronizeFrameRateLock();
        engine_runtime.HandleWindowPollEvents();
    }

    audio_system.TerminateAudioContext();
    engine_runtime.TerminateGraphicsContext();
    return 0;
}
