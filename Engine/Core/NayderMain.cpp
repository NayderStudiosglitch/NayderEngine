#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "../Renderer/Terrain.cpp"
#include "../Renderer/ParticleSystem.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Physics/Collision.cpp"
#include "../Animation/Animation.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/NavMesh.cpp"
#include "../Network/Replication.cpp"
#include "../Editor/EditorTools.cpp" // Linked modularly
#include "SaveLoadCore.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.83] - REAL-TIME WORLD EDITOR" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 DEV LAYER INTEGRATION COMPLETE:" << std::endl;
    std::cout << "  v0.0.81 Navigation Mesh  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.82 Multiplayer Sync -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.83 Editor Tools     -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.84 Packaging System -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    EditorSandboxTools development_console;

    // Simulate developer working on the sandbox layout for Desert Ghost City
    std::cout << "🎬 [SANDBOX ACTIVE]: Launching editor viewport session..." << std::endl;

    // 1. Click on flat terrain zone and drop an abandoned house mesh
    development_console.ExecuteGridRaycastSpawn(PlacementType::MESH_HOUSE, 12.0f, 0.0f, -4.5f, 1.0f);

    // 2. Add an intense zombie spawn node near the building structure
    development_console.ExecuteGridRaycastSpawn(PlacementType::ZOMBIE_SPAWNER, 15.5f, 0.0f, -2.0f, 0.5f);

    // 3. Place a crucial tactical ammunition drop item on the lari
    development_console.ExecuteGridRaycastSpawn(PlacementType::AMMO_BOX, 8.0f, 0.2f, 10.0f, 1.2f);

    // 4. Serialize the entire sandbox workspace straight out to disk!
    development_console.ExportSandboxMapFile();

    std::cout << "\n🎬 [SYSTEM DISPLAY MAP]: Refreshing editor frame buffer views..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
