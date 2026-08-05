#include "Renderer.h"
#include <iostream>

NayderOpenGLRenderer::NayderOpenGLRenderer() {
    window = nullptr;
}

bool NayderOpenGLRenderer::InitializeWindowContext(int width, int height, std::string title) {
    screen_width = width;
    screen_height = height;
    window_title = title;

    if (!glfwInit()) {
        std::cerr << " 🚫 [OPENGL ERROR]: GLFW Initialization failed!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // Fallback to 2.1 Compatibility profile for pure legacy client states
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(screen_width, screen_height, window_title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << " 🚫 [WINDOW ERROR]: Failed to create GLFW Real Window Graphic Box!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Lock frame swap intervals to display monitor's hardware rate

    std::cout << "\n🪟 [REAL WINDOW RUNTIME ACTIVE]:" << std::endl;
    std::cout << " -> Window Node  : " << screen_width << "x" << screen_height << " HD Desktop Profile Mode" << std::endl;
    std::cout << " -> GPU Context  : OpenGL Hardware pipeline initialized successfully!" << std::endl;
    std::cout << " -> STATUS       : ✅ Real Window successfully active on Chromebook screen!" << std::endl;

    return true;
}

void NayderOpenGLRenderer::SetupRealGraphicsPipeline() {
    // Enable core 3D graphics parameters directly inside the hardware driver
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Set viewport drawing projection metrics
    glViewport(0, 0, screen_width, screen_height);
    
    std::cout << " 📐 [OPENGL MATRIX INITIALIZER]: Core hardware viewport bounds locked to rendering target indices." << std::endl;
}

void NayderOpenGLRenderer::ClearScreenBuffer() {
    // Real hardware command wiping the screen buffer color channels using your deep dark matte profile
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NayderOpenGLRenderer::DrawHardwarePrimitiveTriangle() {
    // 1. Pack pure tridimensional float vertex coordinate streams into system memory
    static const float vertices[] = {
         0.0f,  0.5f, 0.0f,  // Top node
        -0.5f, -0.5f, 0.0f,  // Bottom left node
         0.5f, -0.5f, 0.0f   // Bottom right node
    };

    // 2. Pack corresponding color data blocks (Red, Green, Blue interpolation maps)
    static const float colors[] = {
        1.0f, 0.0f, 0.0f,  // Red
        0.0f, 1.0f, 0.0f,  // Green
        0.0f, 0.0f, 1.0f   // Blue
    };

    // 3. Command the GPU state machine to accept client data pointer streams
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Bind array slots straight into active hardware vector layouts
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    // 4. EXECUTE LIVE HARDWARE RASTERIZATION DRAW CALL!
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Disable client state arrays to prevent pipeline cross-memory corruption
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void NayderOpenGLRenderer::HandleWindowPollEvents() {
    glfwPollEvents();
}

bool NayderOpenGLRenderer::ShouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void NayderOpenGLRenderer::SwapHardwareBuffers() {
    glfwSwapBuffers(window);
}

void NayderOpenGLRenderer::TerminateGraphicsContext() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
    std::cout << "\n🧹 [ENGINE SHUTDOWN]: Graphics hardware device context terminated safely." << std::endl;
}
