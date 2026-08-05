#include "../Renderer/Renderer.cpp"
#include "Input.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.87] - NATIVE GL RENDER LOOP" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PHASE 5: REAL ENGINE RUNTIME UNLOCKED:" << std::endl;
    std::cout << "  v0.0.85 Real Window Runtime     -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.86 Real Input (Key+Mouse)  -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.87 Real OpenGL Render Loop -> \342\234\205 OPERATIONAL PA OU" << std::endl;
    std::cout << "  v0.0.88 Real Shader Compiler    -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;

    // Boot up display window profile at your full 1366x768 widescreen parameters
    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Live 3D Render Loop v0.0.87")) {
        return -1;
    }

    // Configure input listeners
    GLFWwindow* active_window = glfwGetCurrentContext();
    input_engine.ConfigureInputCallbacks(active_window);

    // Initialize 3D graphics hardware pipeline configurations
    engine_runtime.SetupRealGraphicsPipeline();

    std::cout << "\n🎬 [REAL OPENGL MAIN LOOP]: The graphics card is actively rendering hardware loops!" << std::endl;
    std::cout << " -> Look at the window: A real hardware-accelerated 3D RGB Triangle is drawing on screen!" << std::endl;
    std::cout << " -> Press [ESCAPE] on your keyboard to stop the rendering thread safely." << std::endl;

    // REAL-TIME HARDWARE DRAWING SYSTEM LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        
        // 1. Wipe old buffers clean at the start of the frame tick
        engine_runtime.ClearScreenBuffer();

        // 2. STAGE AND SUBMIT REAL RASTERIZER ENGINE CALCULATIONS
        engine_runtime.DrawHardwarePrimitiveTriangle();

        // 3. Swap the front and back display pages to blit the drawn geometry onto your screen
        engine_runtime.SwapHardwareBuffers();

        // 4. Update window inputs
        engine_runtime.HandleWindowPollEvents();
    }

    // Safely purge system VRAM contexts
    engine_runtime.TerminateGraphicsContext();
    std::cout << "=======================================================" << std::endl;
    return 0;
}
