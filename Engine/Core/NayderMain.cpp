#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "../Renderer/Terrain.cpp"
#include "../Renderer/ParticleSystem.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Renderer/AssetManager.cpp"
#include "../Physics/Collision.cpp" // Ploge ranje nèt kounye a!
#include "../Animation/Animation.cpp"
#include "../Audio/Audio.cpp"
#include "SaveLoadCore.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.79] - CENTRAL ASSET MANAGER" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 SYSTEM INTEGRATION PROGRESS MAP:" << std::endl;
    std::cout << "  v0.0.77 UI / HUD Engine  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.78 Save & Load Core -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.79 Asset Manager    -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.80 Animation Graph  -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderAssetManager assets;

    // 1. Simulate 10-Player Klan oswa Horde chajman: N ap mande pou l chaje modèl jwè a plizyè fwa
    std::cout << "🎬 [WORLD GENERATOR]: Spawning Player Squad (10 Players connecting)..." << std::endl;
    
    // Premye fwa (Cache Miss -> L ap li diskèt la)
    assets.Request3DModelAsset("Haitian_Soldier_Mesh", "Assets/Models/soldier.obj");
    
    // Dezyèm fwa (Cache Hit -> L ap pataje memwa a automatic san okenn lag!)
    assets.Request3DModelAsset("Haitian_Soldier_Mesh", "Assets/Models/soldier.obj");
    assets.Request3DModelAsset("Haitian_Soldier_Mesh", "Assets/Models/soldier.obj");

    // 2. Chaje Tèkstire yo
    assets.RequestTextureAsset("Brick_Wall_Tex", "Assets/Textures/house_brick.jpg");
    assets.RequestTextureAsset("Brick_Wall_Tex", "Assets/Textures/house_brick.jpg"); // Cache hit!

    // 3. Netwaye memwa a nan background nan
    assets.ClearUnusedBuffers();

    std::cout << "\n🎬 [SYSTEM REPLICATION]: Flushing buffers and swapping frames..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
