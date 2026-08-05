#include "../Renderer/Renderer.cpp"
#include "Input.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.86] - REAL INPUT RUNTIME" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PHASE 5: REAL ENGINE RUNTIME UNLOCKED:" << std::endl;
    std::cout << "  v0.0.85 Real Window Runtime     -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.86 Real Input (Key+Mouse)  -> \342\234\205 OPERATIONAL PA OU" << std::endl;
    std::cout << "  v0.0.87 Real OpenGL Render Loop -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;

    // Initialize 1366x768 widescreen display window profile
    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Real Input System v0.0.86")) {
        return -1;
    }

    // Recover the GLFW window handle from inside our renderer module to attach input hooks
    GLFWwindow* active_window = glfwGetCurrentContext();
    input_engine.ConfigureInputCallbacks(active_window);

    std::cout << "\n🎬 [REAL RUNTIME GAME LOOP]: Input listeners running at 60Hz tick rates." << std::endl;
    std::cout << " -> Move your mouse to test real-time 360 rotation loops in terminal output!" << std::endl;
    std::cout << " -> Press [W, A, S, D] keys to track live status updates." << std::endl;
    std::cout << " -> Press [ESCAPE] on your keyboard to securely kill the game loop process." << std::endl;

    float current_yaw = 0.0f, current_pitch = 0.0f;

    // CORE HARDCORE INTERACTIVE RUNTIME LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_runtime.ClearScreenBuffer();

        // 1. Process Live Keyboard Key Arrays
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            std::cout << " 🎮 [KEY EVENT]: Holding W -> Translating player character velocity FORWARD." << std::endl;
        }
        if (NayderInputSystem::key_states[GLFW_KEY_S]) {
            std::cout << " 🎮 [KEY EVENT]: Holding S -> Translating player character velocity BACKWARD." << std::endl;
        }

        // 2. Process Live Mouse Orientation Coordinates
        float old_yaw = current_yaw;
        NayderInputSystem::GetCameraOrientation(current_yaw, current_pitch);
        if (current_yaw != old_yaw) {
            std::cout << " 🖱️  [MOUSE EVENT]: 360 Rotation Updated -> Yaw: " << current_yaw << "° │ Pitch: " << current_pitch << "°" << std::endl;
        }

        engine_runtime.SwapHardwareBuffers();
        engine_runtime.HandleWindowPollEvents(); // Keeps checking hardware states
    }

    engine_runtime.TerminateGraphicsContext();
    std::cout << "=======================================================" << std::endl;
    return 0;
}
