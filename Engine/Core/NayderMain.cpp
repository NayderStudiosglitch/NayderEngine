#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.72] - REAL-TIME SHADOW MAPPING" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 ADVANCED GRAPHICS STACK COMPLETE:" << std::endl;
    std::cout << "  v0.0.70 Material System  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.71 Lighting Engine  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.72 Shadow Mapping   -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.73 Terrain Renderer -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderOBJLoader obj_loader;
    NayderTextureSystem texture_engine;
    NayderMaterialSystem material_engine;
    NayderLightingEngine lighting_engine;
    NayderShadowEngine shadow_engine;

    // Load assets and light sources
    CompiledMesh house = obj_loader.ParseOBJFile("Assets/Models/house.obj");
    DirectionalLight sun = lighting_engine.CreateSunlight(-0.5f, -1.0f, -0.2f, "SUNSET_CYBERPUNK");
    
    // 1. Initialize the specialized Next-Gen Shadow Buffers
    ShadowFrameBuffer shadow_buffer = shadow_engine.InitializeShadowBuffer();

    // 2. RUN PASS 1: Render scene from the sunlight's eye to extract depth metrics
    shadow_engine.ExecuteFirstPassDepthRender(house.model_name, sun.dir_x, sun.dir_y, sun.dir_z);

    // 3. RUN PASS 2: Switch viewpoint to player camera, cross-examine data, and draw shadows!
    shadow_engine.ExecuteSecondPassShadowSample();

    std::cout << "\n🎬 [GPU MAIN PIPELINE]: Swapping frame buffers with real-time shadow projection map loops..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
