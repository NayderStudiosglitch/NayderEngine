#pragma once
#include <string>

// Ploge vrè Header GLFW pou kreyasyon fenèt nan nivo OS
#include <GLFW/glfw3.h>

class NayderOpenGLRenderer {
private:
    GLFWwindow* window;
    int screen_width;
    int screen_height;
    std::string window_title;

public:
    NayderOpenGLRenderer();
    bool InitializeWindowContext(int width, int height, std::string title);
    void HandleWindowPollEvents();
    bool ShouldWindowClose();
    void ClearScreenBuffer();
    void SwapHardwareBuffers();
    void TerminateGraphicsContext();
};
