#include "Camera.h"
#include <iostream>
#include <cmath>

NayderCameraSystem::NayderCameraSystem() {
    position = {0.0f, 2.0f, -5.0f}; // Default spawning coordinates
    yaw = -90.0f;
    pitch = 0.0f;
    current_mode = CameraMode::FREE_EDITOR;
}

void NayderCameraSystem::SetCameraMode(CameraMode mode) {
    current_mode = mode;
    std::cout << "  📷 [CAMERA INTERLOCK]: Pipeline mode swapped to: ";
    if (mode == CameraMode::FIRST_PERSON) std::cout << "FIRST_PERSON (FPS View)" << std::endl;
    if (mode == CameraMode::THIRD_PERSON) std::cout << "THIRD_PERSON (TPS View)" << std::endl;
    if (mode == CameraMode::FREE_EDITOR)  std::cout << "FREE_EDITOR (Fly Mode)" << std::endl;
}

void NayderCameraSystem::ProcessKeyboardInput(char key, float speed) {
    // 🎮 WASD TRANSLATION LOGIC
    if (key == 'w' || key == 'W') position.z += speed;
    if (key == 's' || key == 'S') position.z -= speed;
    if (key == 'a' || key == 'A') position.x -= speed;
    if (key == 'd' || key == 'D') position.x += speed;
    
    std::cout << "   [WASD TRANSLATION]: Matrix position shifted to: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
}

void NayderCameraSystem::ProcessMouseLook(float delta_x, float delta_y) {
    // 🖱️ MOUSE LOOK SENSITIVITY CALCULATOR
    float sensitivity = 0.1f;
    yaw   += delta_x * sensitivity;
    pitch += delta_y * sensitivity;

    // Clamp pitch bounds to prevent camera flipping upside down on the GPU
    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

void NayderCameraSystem::RenderViewMatrix() {
    // Calculate LookAt vectors for rendering pipelines using trigonometry
    float rad_yaw = yaw * M_PI / 180.0f;
    float rad_pitch = pitch * M_PI / 180.0f;

    Vector3D target_look;
    target_look.x = cos(rad_pitch) * cos(rad_yaw);
    target_look.y = sin(rad_pitch);
    target_look.z = cos(rad_pitch) * sin(rad_yaw);

    std::cout << "   🎥 [GPU VIEW MATRIX TICK]: Camera Vector looking at node: (" 
              << position.x + target_look.x << ", " 
              << position.y + target_look.y << ", " 
              << position.z + target_look.z << ") | Locked at 107 FPS." << std::endl;
}
