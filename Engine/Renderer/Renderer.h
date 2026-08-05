#pragma once
#include <string>
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
    
    // NEW HARDWARE PIPELINE ARRAY FUNCTIONS FOR v0.0.87
    void SetupRealGraphicsPipeline();
    void DrawHardwarePrimitiveTriangle();
    
    void SwapHardwareBuffers();
    void TerminateGraphicsContext();
};
