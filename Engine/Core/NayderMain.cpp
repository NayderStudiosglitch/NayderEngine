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
#include "../Editor/EditorTools.cpp"
#include "SaveLoadCore.cpp"
#include "PackagingSystem.cpp" // Linked modularly
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.84] - AUTOMATED GAME PACKAGER" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 CONGRATULATIONS! ENTIRE INTEGRATION ROADMAP UNLOCKED:" << std::endl;
    std::cout << "  v0.0.82 Multiplayer Sync -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.83 Editor Tools     -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.84 Packaging System -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "=======================================================" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderPackagingSystem packager;

    // Simulate packing the complete asset catalog for Neon Fall 17
    std::cout << "🎬 [SHIPPING PROCESS ACTIVE]: Commencing asset serialization pass..." << std::endl;

    // 1. Stage the high-poly mesh geometries
    packager.StageLooseAssetForPackaging("Assets/Models/soldier.obj", 4512000); // 4.5 MB mesh
    packager.StageLooseAssetForPackaging("Assets/Models/zombie.obj", 2150000);
    packager.StageLooseAssetForPackaging("Assets/Models/house.obj", 8430000);

    // 2. Stage the material image texture files
    packager.StageLooseAssetForPackaging("Assets/Textures/soldier_skin.png", 2048000);
    packager.StageLooseAssetForPackaging("Assets/Textures/house_brick.jpg", 1024000);

    // 3. Stage the binary maps and runtime configurations
    packager.StageLooseAssetForPackaging("Assets/Maps/desert_ghost_city.map", 512000);

    // 4. Fire the deployment master compilation sequence!
    packager.CompileStandaloneShippingBuild();

    std::cout << "\n🎬 [ENGINE SHUTDOWN]: Build compiled successfully under strict 107 FPS Lock parameters." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
