#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp" // Linked modularly
#include "Input.cpp"
#include <iostream>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.91] - HARDWARE LIGHTING RUNTIME" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PHASE 5: REAL ENGINE RUNTIME UNLOCKED:" << std::endl;
    std::cout << "  v0.0.89 Real Mesh Rendering    -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.90 Real Texture Rendering -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.91 Real Lighting          -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.92 Real Physics Context   -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;
    NayderLightingRuntime lighting_system;

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Hardware Shading v0.0.91")) {
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

    CompiledMesh zombie_mesh = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    unsigned int VAO, VBO, EBO;
    obj_loader.UploadMeshToGPU(zombie_mesh, VAO, VBO, EBO);

    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    std::cout << "\n🎬 [REAL LIGHTED RUNTIME RUNNING]: Executing pixel shader vector dot products!" << std::endl;
    std::cout << " -> The hardware is actively calculating specular and diffuse values across the meshes!" << std::endl;

    // HARDCORE INTERACTIVE RUNTIME RENDERING LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_runtime.ClearScreenBuffer();

        shader_compiler.UseShaderProgram();

        // 1. Inject real sun parameters into the GLSL program variables every frame
        // Simulating the warm orange sunset color scheme from your Escape Land artwork profile!
        lighting_system.SetDirectionalSunUniforms(shader_compiler.ProgramID, -0.5f, -1.0f, -0.2f, 1.0f, 0.55f, 0.2f);
        
        // Pass simulated developer tracking view positions
        lighting_system.UpdateCameraViewPositionUniform(shader_compiler.ProgramID, 0.0f, 2.0f, -5.0f);

        texture_system.BindTextureUnit(0);

        if (glBindVertexArray_ptr) {
            glBindVertexArray_ptr(VAO);
        }

        glDrawElements(GL_TRIANGLES, zombie_mesh.total_indices, GL_UNSIGNED_INT, 0);

        engine_runtime.SwapHardwareBuffers();
        engine_runtime.HandleWindowPollEvents();
    }

    engine_runtime.TerminateGraphicsContext();
    std::cout << "=======================================================" << std::endl;
    return 0;
}
