#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "Input.cpp"
#include <iostream>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.90] - NATIVE TEXTURE SAMPLER" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PHASE 5: REAL ENGINE RUNTIME UNLOCKED:" << std::endl;
    std::cout << "  v0.0.88 Real Shader Compiler   -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.89 Real Mesh Rendering    -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.90 Real Texture Rendering -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.91 Real Lighting          -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    NayderOBJLoader obj_loader;
    NayderTextureRuntime texture_system;

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Hardware Texture Map v0.0.90")) {
        return -1;
    }

    GLFWwindow* active_window = glfwGetCurrentContext();
    input_engine.ConfigureInputCallbacks(active_window);
    engine_runtime.SetupRealGraphicsPipeline();

    // Compile GLSL code layers
    if (!shader_compiler.LoadAndCompileShaders("Assets/Shaders/Basic3D.vert", "Assets/Shaders/Basic3D.frag")) {
        return -1;
    }

    // LOAD ACTUAL BMP TEXTURE INTO VRAM
    if (!texture_system.LoadRealBMPTexture("Assets/Textures/zombie_diffuse.bmp")) {
        return -1;
    }

    CompiledMesh zombie_mesh = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    unsigned int VAO, VBO, EBO;
    obj_loader.UploadMeshToGPU(zombie_mesh, VAO, VBO, EBO);

    PFNGLBINDVERTEXARRAYPROC  glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
    
    std::cout << "\n🎬 [REAL TEXTURED RUNTIME RUNNING]: Pushing color maps directly to active surfaces!" << std::endl;
    std::cout << " -> The GPU is currently blitting raw textured pixels straight across the 3D geometry matrix!" << std::endl;

    // HARDCORE ACTIVE RENDERING LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_runtime.ClearScreenBuffer();

        shader_compiler.UseShaderProgram();

        // Bind the image data into active Texture Unit 0 prior to rendering submissions
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
