#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "../Renderer/Terrain.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.73] - HIGH-POLY 3D TERRAIN CORE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 3D WORLD INTEGRATION ROADMAP UPDATE:" << std::endl;
    std::cout << "  v0.0.71 Lighting Engine  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.72 Shadow Mapping   -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.73 Terrain Renderer -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.74 Animation System -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderOBJLoader obj_loader;
    NayderTextureSystem texture_engine;
    NayderTerrainRenderer terrain_engine;

    // 1. Chaje modèl ak kouch nan sèn nan
    CompiledMesh zombie = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    TextureData ground_grass_tex = texture_engine.LoadTextureFromFile("Assets/Textures/terrain_grass.jpg");

    // 2. Chaje ak Kalkile vrè Heightmap Open World la nan nivo sistèm nan!
    // Jenere yon gwo katab grid 512x512 piksèl altitid pou gwo zile a
    TerrainMesh island_terrain = terrain_engine.GenerateTerrainFromHeightmap("Assets/Maps/island_heightmap.png", 512, 512);
    terrain_engine.UploadTerrainToVRAM(island_terrain);

    // 3. Lanse kòmand desen mòn yo sou ekran an
    terrain_engine.RenderTerrainMesh();

    std::cout << "\n🎬 [DISPLAY BUFFER]: Swapping double frames. 3D Terrain world space rendered successfully!" << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
