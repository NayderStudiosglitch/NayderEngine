#include "MainMenu.h"
#include <iostream>

NayderMainMenuEngine::NayderMainMenuEngine() {}

void NayderMainMenuEngine::RenderFrontendCanvas(int active_fps) {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     🎨 [NEON FALL 17] - CORE MAIN MENU DASHBOARD" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << "  [ ENGINE RUNTIME PERFORMANCE STATUS: " << active_fps << " FPS LOCK ]" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "   👉  [1] - START NEW CHALLENGE (Initialize Sandbox Grid)" << std::endl;
    std::cout << "   👉  [2] - CONTINUE SURVIVAL   (Load State Sync File)" << std::endl;
    std::cout << "   👉  [3] - TERMINATE PROCESS   (Secure OS Shutdown)" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << " ENTER SELECTION VALUE ON YOUR KEYBOARD (1-3): ";
}

EngineSystemState NayderMainMenuEngine::EvaluateSelectionInput(char user_choice_token) {
    if (user_choice_token == '1') {
        std::cout << "\n🚀 [FRONTEND OVERRIDE]: Allocating pristine world matrices..." << std::endl;
        std::cout << " -> Instantiating entity clusters. Streaming viewport vectors..." << std::endl;
        return EngineSystemState::RUNTIME_GAMEPLAY;
    }
    else if (user_choice_token == '2') {
        std::cout << "\n📂 [FRONTEND OVERRIDE]: Initializing filesystem persistence bridge..." << std::endl;
        return EngineSystemState::RUNTIME_GAMEPLAY;
    }
    else if (user_choice_token == '3') {
        std::cout << "\n🧹 [FRONTEND OVERRIDE]: Safe exit command intercepted." << std::endl;
        return EngineSystemState::SHUTDOWN_SEQUENCE;
    }
    
    std::cout << " ❌ [INVALID SELECTION]: Unknown menu option. Re-centering viewport canvas." << std::endl;
    return EngineSystemState::FRONTEND_MENU;
}
