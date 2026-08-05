#include "../Renderer/Renderer.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.85] - REAL WINDOW RUNTIME" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PHASE 5: REAL ENGINE RUNTIME UNLOCKED:" << std::endl;
    std::cout << "  v0.0.85 Real Window Runtime     -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.86 Real Input (Key+Mouse)  -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;

    // LOUVRI VRÈ FÈNÈT JWÈT LA SOU EKRAAN AN (1366x768 Computer Resolution)
    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Real Runtime Build v0.0.85")) {
        return -1;
    }

    std::cout << "\n🎬 [ENGINE CORE LOOP]: Launching real window cycle. Close the graphic window to stop." << std::endl;

    // VRÈ BOUK JWÈT LA (Real Game Loop Framework)
    while (!engine_runtime.ShouldWindowClose()) {
        
        // 1. Netwaye ekran an chak frame
        engine_runtime.ClearScreenBuffer();

        // (Isit la se kote nou pral ploge kòd desine triyang ak objè 3D yo nan v0.0.87)

        // 2. Chanje buffer kat grafik la pou afiche desen an
        engine_runtime.SwapHardwareBuffers();

        // 3. Tcheke si jwè a peze klavye oswa sourit
        engine_runtime.HandleWindowPollEvents();
    }

    // Fèmen pyebwa kòmand lan lè fenèt la fèmen
    engine_runtime.TerminateGraphicsContext();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
