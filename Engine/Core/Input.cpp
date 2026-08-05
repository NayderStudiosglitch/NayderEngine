#include "Input.h"
#include <iostream>

// Initialize active static memory blocks
bool NayderInputSystem::key_states[1024] = { false };
float NayderInputSystem::mouse_last_x = 1366.0f / 2.0f;
float NayderInputSystem::mouse_last_y = 768.0f / 2.0f;
float NayderInputSystem::camera_yaw = -90.0f;
float NayderInputSystem::camera_pitch = 0.0f;
bool NayderInputSystem::first_mouse_event = true;

NayderInputSystem::NayderInputSystem() {}

void NayderInputSystem::ConfigureInputCallbacks(GLFWwindow* window_handle) {
    // Lock and capture the hardware mouse directly inside our window viewport boundaries
    glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Register structural OS hooks to bypass standard terminal streams
    glfwSetKeyCallback(window_handle, NayderInputSystem::NativeKeyCallback);
    glfwSetCursorPosCallback(window_handle, reinterpret_cast<GLFWcursorposfun>(NayderInputSystem::NativeCursorPosCallback));
    
    std::cout << " ⌨️  [REAL INPUT PIPELINE]: Connected native hardware callback gates to OS input buffers." << std::endl;
    std::cout << " -> Mouse Status : HARDWARE GRAB ACTIVE (Cursor disabled, locked to window center)." << std::endl;
    std::cout << " -> STATUS       : ✅ Real keyboard & mouse input matrices operational on GLFW context!" << std::endl;
}

void NayderInputSystem::NativeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)   key_states[key] = true;
        if (action == GLFW_RELEASE) key_states[key] = false;
    }
    
    // Instant escape key override to close the window securely
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void NayderInputSystem::NativeCursorPosCallback(GLFWwindow* window, double xpos, float ypos) {
    if (first_mouse_event) {
        mouse_last_x = static_cast<float>(xpos);
        mouse_last_y = ypos;
        first_mouse_event = false;
    }

    float delta_x = static_cast<float>(xpos) - mouse_last_x;
    float delta_y = mouse_last_y - ypos; // Reversed since y-coordinates go from bottom to top
    
    mouse_last_x = static_cast<float>(xpos);
    mouse_last_y = ypos;

    float mouse_sensitivity = 0.1f;
    camera_yaw   += delta_x * mouse_sensitivity;
    camera_pitch += delta_y * mouse_sensitivity;

    // Clamp pitch bounds to protect matrix calculations from flipping upside down
    if (camera_pitch > 89.0f)  camera_pitch = 89.0f;
    if (camera_pitch < -89.0f) camera_pitch = -89.0f;
}

void NayderInputSystem::GetCameraOrientation(float& out_yaw, float& out_pitch) {
    out_yaw = camera_yaw;
    out_pitch = camera_pitch;
}
