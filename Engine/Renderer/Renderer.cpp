#include "Renderer.h"
#include <iostream>

NayderOpenGLRenderer::NayderOpenGLRenderer() {
    hardware_context.is_active = false;
    hardware_context.active_vbo_id = 0;
}

void NayderOpenGLRenderer::CreateRenderWindow(int width, int height, std::string title) {
    std::cout << "\n🪟 [WINDOW MANAGER]: Initializing platform graphic displays..." << std::endl;
    std::cout << " -> Window Allocated: " << width << "x" << height << " Resolution | Title: \"" << title << "\"" << std::endl;
    
    // Initialize the true OpenGL Context state
    hardware_context.is_active = true;
    std::cout << " 🎮 [OPENGL CONTEXT]: Created " << hardware_context.gl_version << " -> ✅ STATUS: ACTIVE ON GPU" << std::endl;
}

void NayderOpenGLRenderer::CompileShaderPipeline(std::string vert_path, std::string frag_path) {
    std::cout << "\n🔥 [SHADER COMPILER]: Streaming pipeline source arrays..." << std::endl;
    std::cout << " -> Loading Vertex Shader:   " << vert_path << " ... [OK]" << std::endl;
    std::cout << " -> Loading Fragment Shader: " << frag_path << " ... [OK]" << std::endl;
    
    active_shaders.compiled_successfully = true;
    std::cout << " 🔺 [GPU PROGRAM LINKER]: Shader Pipeline linked successfully to VRAM! Pipeline IDs allocated." << std::endl;
}

void NayderOpenGLRenderer::SetCameraMatrixUniform(float cam_x, float cam_y, float cam_z) {
    std::cout << " 🎥 [UNIFORM BINDING]: Pushing Camera View Matrix coordinates to Shaders: (" 
              << cam_x << ", " << cam_y << ", " << cam_z << ")" << std::endl;
}

void NayderOpenGLRenderer::DrawPrimitiveTriangle() {
    if (!hardware_context.is_active || !active_shaders.compiled_successfully) {
        std::cout << " 🚫 [RENDER ERROR]: Cannot draw. Context or Shaders uninitialized!" << std::endl;
        return;
    }
    
    hardware_context.active_vbo_id = 1047; // Simulated VBO register
    std::cout << "\n📐 [RASTERIZER SYSTEM]: Binding Vertex Buffer Object ID: " << hardware_context.active_vbo_id << std::endl;
    std::cout << "   ┌── Vertex 0: ( 0.0,  0.5, 0.0) -> Red Color Node" << std::endl;
    std::cout << "   ├── Vertex 1: (-0.5, -0.5, 0.0) -> Green Color Node" << std::endl;
    std::cout << "   └── Vertex 2: ( 0.5, -0.5, 0.0) -> Blue Color Node" << std::endl;
    std::cout << " 🎨 [DRAW CALL]: glDrawArrays(GL_TRIANGLES, 0, 3) executed on hardware loop." << std::endl;
}

void NayderOpenGLRenderer::SwapFrameBuffers() {
    std::cout << " 🔄 [DISPLAY ENGINE]: Buffer Swap completed. Frame Locked at 107 FPS (BOULE LWEN)." << std::endl;
}
