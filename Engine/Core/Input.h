#pragma once
#include <GLFW/glfw3.h>

class NayderInputSystem {
private:
    static float mouse_last_x;
    static float mouse_last_y;
    static float camera_yaw;
    static float camera_pitch;
    static bool first_mouse_event;

public:
    static bool key_states[1024];

    NayderInputSystem();
    void ConfigureInputCallbacks(GLFWwindow* window_handle);
    
    static void NativeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void NativeCursorPosCallback(GLFWwindow* window, double xpos, float ypos);
    
    static void GetCameraOrientation(float& out_yaw, float& out_pitch);
};
