#include "../Renderer/Renderer.cpp"
#include "Camera.cpp" // Included modularly
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.67] - NATIVE OPENGL RENDERER" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 MILESTONE STATUS UPDATE:" << std::endl;
    std::cout << "  v0.0.65 3D Box Collision -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.66 Camera Subsystem -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.67 OpenGL Renderer  -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.68 OBJ Model Loader -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // 1. Initialize the Advanced Window and Context Layer
    NayderOpenGLRenderer renderer;
    renderer.CreateRenderWindow(1920, 1080, "Neon Fall 17 - Runtime Viewport Zone");

    // 2. Stream and link the structural assets
    renderer.CompileShaderPipeline("Assets/Shaders/Basic3D.vert", "Assets/Shaders/Basic3D.frag");

    // 3. Instantiate the camera and bind the transformation coordinates to the GPU
    NayderCameraSystem core_camera;
    std::cout << "\n[CAMERA LINK]: Reading active viewport position parameters..." << std::endl;
    core_camera.ProcessKeyboardInput('w', 4.5f); // Move viewpoint forward
    
    // Bind uniform matrix values to our shader program
    renderer.SetCameraMatrixUniform(0.0f, 2.0f, -0.5f);

    // 4. Fire off the actual 3D primitive drawing pipelines!
    renderer.DrawPrimitiveTriangle();
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
