#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Editor/EditorWorkspace.cpp"
#include "../Editor/GizmoEngine.cpp" // Interlocking real Gizmo transformation handles modularly
#include "../Physics/Collision.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/ZombieAI.cpp"
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
    std::cout << "     [NAYDER ENGINE v0.2.1] - INTERACTIVE GIZMO ENGINE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 DESKTOP WORKSPACE RECONSTRUCTION PROGRESS MAP:" << std::endl;
    std::cout << "  v0.2.0 Nayder Engine Editor -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.2.1 Interactive Gizmos   -> \342\234\205 OPERATIONAL PA OU" << std::endl;
    std::cout << "  v0.2.2 Scene Save/Load Core -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;
    NayderEditorWorkspace editor_suite;
    NayderGizmoEngine gizmo_engine;
    NayderAudioRuntime audio_system;
    NayderGameLoopClock engine_clock(107.0);

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Nayder Workspace Engine Editor v0.2.1")) {
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

    // Initial selected asset node metrics parameters
    SelectedEntityData selected_node = { "Zombie_01", 16.5f, 0.0f, -2.4f, 0.0f, 45.0f, 0.0f, 1.2f, "zombie.obj" };
    GizmoMode current_active_tool = GizmoMode::MOVE_TRANSLATE;

    bool key_6_released = true, key_7_released = true, key_8_released = true;

    std::cout << "\n🚀 [GIZMO SUITE INITIALIZED - HOTKEYS ACTIVE]:" << std::endl;
    std::cout << " -> Tap key [6] on keyboard to initialize MOVE handles." << std::endl;
    std::cout << " -> Tap key [7] on keyboard to initialize ROTATE handles." << std::endl;
    std::cout << " -> Tap key [8] on keyboard to initialize SCALE handles." << std::endl;
    std::cout << " -> HOLD [W] key to actively apply transform calculations onto the asset!" << std::endl;

    // MASTER ENGINE RUNTIME TICK WORKSPACE LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // 1. MONITOR HARDWARE OS INPUT INTERRUPTS FOR GIZMO SELECTIONS
        if (NayderInputSystem::key_states[GLFW_KEY_6]) {
            if (key_6_released) { current_active_tool = GizmoMode::MOVE_TRANSLATE; gizmo_engine.SetActiveGizmoMode(current_active_tool); key_6_released = false; }
        } else { key_6_released = true; }

        if (NayderInputSystem::key_states[GLFW_KEY_7]) {
            if (key_7_released) { current_active_tool = GizmoMode::ROTATE_DEG; gizmo_engine.SetActiveGizmoMode(current_active_tool); key_7_released = false; }
        } else { key_7_released = true; }

        if (NayderInputSystem::key_states[GLFW_KEY_8]) {
            if (key_8_released) { current_active_tool = GizmoMode::SCALE_UNIFORM; gizmo_engine.SetActiveGizmoMode(current_active_tool); key_8_released = false; }
        } else { key_8_released = true; }

        // 2. APPLY TRANSFORMATIONS MODIFICATIONS BASED ON ACTIVE SELECTION VALUE
        float transformation_input = 0.0f;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            transformation_input = 1.0f; // Actively feeding positive force vectors
        }

        if (transformation_input != 0.0f) {
            gizmo_engine.ApplyGizmoTransformDelta(current_active_tool, transformation_input, selected_node.pos_x, selected_node.rot_y, selected_node.scale, dt);
        }

        // Draw passes stage scripts
        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram();

        // Pass 1: Viewport renders
        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, 0.0f, 2.0f, -5.0f);
        texture_system.BindTextureUnit(0);

        PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
        if (glBindVertexArray_ptr) { glBindVertexArray_ptr(VAO); }
        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        // 3. SUBMIT REAL-TIME GIZMO LINE DRAW CALCULATIONS INTO THE INTERRUPT PIPELINE
        gizmo_engine.RenderActiveGizmoHandles(selected_node.pos_x, selected_node.pos_y, selected_node.pos_z);

        // Pass 2: Overwrite split layout dashboards
        editor_suite.SetEditorLayoutMatrix();
        editor_suite.DrawSceneHierarchyPanel();
        editor_suite.DrawCentralViewportPanel();
        
        // Update the inspector display title dynamically to trace active tools!
        selected_node.mesh_source = "zombie.obj [" + gizmo_engine.GetCurrentToolLabel() + "]";
        editor_suite.DrawInspectorPanel(selected_node);
        
        editor_suite.DrawContentBrowserPanel();

        engine_runtime.SwapHardwareBuffers();
        engine_clock.SynchronizeFrameRateLock();
        engine_runtime.HandleWindowPollEvents();
    }

    audio_system.TerminateAudioContext();
    engine_runtime.TerminateGraphicsContext();
    return 0;
}
