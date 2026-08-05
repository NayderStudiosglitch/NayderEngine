#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "../Renderer/Terrain.cpp"
#include "../Renderer/ParticleSystem.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Animation/Animation.cpp"
#include "../Audio/Audio.cpp"
#include "SaveLoadCore.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.78] - GAME PERSISTENCE CORE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 INTEGRATION PIPELINE PROGRESS MATRIX:" << std::endl;
    std::cout << "  v0.0.76 Particle System  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.77 UI / HUD Engine  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.78 Save & Load Core -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.79 Asset Manager    -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderSaveLoadEngine persistence_engine;

    // 1. Simulate active gameplay scenario: Player reaches Day 23 in Hardcore Mode
    GameSaveState active_session;
    active_session.saved_day = 23;
    active_session.player_hp = 85;
    active_session.player_armor = 40;
    active_session.total_ammo = 150;
    active_session.zombies_killed = 1248;
    active_session.current_map = "Desert_Ghost_City_Alpha";

    // Trigger Save Process
    persistence_engine.WriteSaveGameToDisk(active_session);

    std::cout << "\n-------------------------------------------------------" << std::endl;

    // 2. Simulate subsequent game launch: Restoring data from local storage
    GameSaveState loaded_session;
    if (persistence_engine.ReadSaveGameFromDisk(loaded_session)) {
        std::cout << " 🎮 [GAMEPLAY RESTART]: Synchronization successful across memory slots!" << std::endl;
        std::cout << " -> Running Zombie Zone Loop at Day " << loaded_session.saved_day << " with " << loaded_session.total_ammo << " rounds loaded." << std::endl;
    }

    std::cout << "\n🎬 [ENGINE CORE]: Swapping frame buffers..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
