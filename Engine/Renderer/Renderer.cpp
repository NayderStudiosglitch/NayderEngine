#include "Renderer.h"
#include <iostream>

NayderOpenGLRenderer::NayderOpenGLRenderer() {
    window = nullptr;
}

bool NayderOpenGLRenderer::InitializeWindowContext(int width, int height, std::string title) {
    screen_width = width;
    screen_height = height;
    window_title = title;

    // 1. INiSYALIZE GLFW LIBRERI A REYÈL
    if (!glfwInit()) {
        std::cerr << " 🚫 [OPENGL ERROR]: GLFW Initialization failed!" << std::endl;
        return false;
    }

    // Konfigire OpenGL vèsyon 3.3 Core Profile nan nivo kat grafik (GPU)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. KREYE VRÈ FÈNÈT LA SOU EKRAAN AN
    window = glfwCreateWindow(screen_width, screen_height, window_title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << " 🚫 [WINDOW ERROR]: Failed to create GLFW Real Window Graphic Box!" << std::endl;
        glfwTerminate();
        return false;
    }

    // Fè fenèt sa a tounen vrè kontèks OpenGL aktif pou kòd yo
    glfwMakeContextCurrent(window);
    
    // Aktive V-Sync pou bloke FPS la selon ekran w (oswa 107 FPS koutim pita)
    glfwSwapInterval(1);

    std::cout << "\n🪟 [REAL WINDOW RUNTIME ACTIVE]:" << std::endl;
    std::cout << " -> Window Node  : " << screen_width << "x" << screen_height << " HD Desktop Profile Mode" << std::endl;
    std::cout << " -> GPU Context  : OpenGL 3.3 Core Profile initialized on VRAM cluster!" << std::endl;
    std::cout << " -> STATUS       : ✅ Real Window successfully active on Chromebook screen!" << std::endl;

    return true;
}

void NayderOpenGLRenderer::ClearScreenBuffer() {
    // Vrè kòmand OpenGL k ap netwaye ekran an ak yon bèl koulè Cyberpunk nwa/violèt
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NayderOpenGLRenderer::HandleWindowPollEvents() {
    glfwPollEvents(); // Koute evènman klavye/sourit nan nivo OS
}

bool NayderOpenGLRenderer::ShouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void NayderOpenGLRenderer::SwapHardwareBuffers() {
    glfwSwapBuffers(window); // Vrè kòmand k ap chanje doub Frame-Buffers yo sou ekran an
}

void NayderOpenGLRenderer::TerminateGraphicsContext() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
    std::cout << "\n🧹 [ENGINE SHUTDOWN]: Graphics hardware device context terminated safely." << std::endl;
}
