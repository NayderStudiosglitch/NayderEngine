#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Renderer/WorldRenderer.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include <iostream>

// Rele varyab global ki anndan WorldRenderer a pou n ka kontwole yo ak klavye a
extern float global_cam_x;
extern float global_cam_y;
extern float global_cam_z;

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "  👑 [NAYDER ENGINE v0.4.0] - MULTI-MODULE 3D CORE" << std::endl;
    std::cout << "=======================================================" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderGameLoopClock engine_clock(107.0);

    // Lanse chofè fenèt la an Compatibility mode pou evite Core Profile restriction
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    GLFWwindow* active_window = glfwCreateWindow(1366, 768, "Neon Fall 17 - First Real 3D World View v0.4.0", nullptr, nullptr);
    if (!active_window) {
        std::cerr << "🚫 [ERROR]: Window allocation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(active_window);
    glfwSwapInterval(1);

    input_engine.ConfigureInputCallbacks(active_window);
    
    // Asire nou sourit la vizib epi lib pou premye tès sa a
    glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glEnable(GL_DEPTH_TEST); // Aktive Z-Buffer depth testing pou pwofondè fèm!
    glViewport(0, 0, 1366, 768);

    // Inisyalize Modil World la
    WorldRenderer::Initialize();

    std::cout << "\n🎬 [3D PIPELINE RUNTIME LIVE]: Use [W, S, A, D] to walk dynamically inside the 3D world!" << std::endl;

    // MAIN GAME LOOP UNIFIED FRAME TICK
    while (!glfwWindowShouldClose(active_window)) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // 🏃‍♂️ KOUTE KLAVYE WASD POU DEPLASE VARYAB KAMERA GLOBAL YO LIVE
        float speed = 6.0f * dt;
        if (glfwGetKey(active_window, GLFW_KEY_W) == GLFW_PRESS) global_cam_z -= speed; // Avanse vè fon sèn nan
        if (glfwGetKey(active_window, GLFW_KEY_S) == GLFW_PRESS) global_cam_z += speed; // Dèyè
        if (glfwGetKey(active_window, GLFW_KEY_A) == GLFW_PRESS) global_cam_x -= speed; // Agoch
        if (glfwGetKey(active_window, GLFW_KEY_D) == GLFW_PRESS) global_cam_x += speed; // Adwat

        // Egzekite desen 3D a nan nivo chofè a
        WorldRenderer::Render();

        glfwSwapBuffers(active_window);
        engine_clock.SynchronizeFrameRateLock();
        glfwPollEvents();
    }

    glfwDestroyWindow(active_window);
    glfwTerminate();
    return 0;
}
