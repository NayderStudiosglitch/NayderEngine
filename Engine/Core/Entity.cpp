#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.66] - MODULAR CAMERA SUBSYSTEM" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 3D WORLD INTEGRATION STATUS LAYERS:" << std::endl;
    std::cout << "  v0.0.61 Entity System    -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.62 Scene Graph      -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.65 3D Collision     -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.66 Camera System    -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.67 OpenGL Renderer  -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderCameraSystem camera;

    // SIMULATION 1: Initialize Editor mode and fly around coordinates
    std::cout << "[PHASE 1]: Editor Mode activated. flying to survey grid fields..." << std::endl;
    camera.SetCameraMode(CameraMode::FREE_EDITOR);
    camera.ProcessKeyboardInput('w', 1.5f); // Move forward
    camera.ProcessKeyboardInput('d', 0.8f); // Strafe right
    camera.RenderViewMatrix();

    // SIMULATION 2: Mouse look adjustment calculations
    std::cout << "\n[PHASE 2]: User pans mouse to view target coordinates..." << std::endl;
    camera.ProcessMouseLook(15.0f, -5.0f); // Mouse shifted on axis matrices
    camera.RenderViewMatrix();

    // SIMULATION 3: Transition view directly inside custom gameplay loops
    std::cout << "\n[PHASE 3]: Launching Neon Fall 17 Zombie Zone - Locking camera inside player..." << std::endl;
    camera.SetCameraMode(CameraMode::FIRST_PERSON);
    camera.ProcessKeyboardInput('w', 2.0f); // Move forward in gameplay
    camera.RenderViewMatrix();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
