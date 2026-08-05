#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.70] - CUSTOM MATERIAL PROFILE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PRODUCTION PIPELINE STATUS MAP:" << std::endl;
    std::cout << "  v0.0.68 OBJ Model Loader -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.69 Texture System   -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.70 Material System  -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.71 Lighting Engine  -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // Inisyalize tout gwo modil motè a
    NayderOpenGLRenderer renderer;
    NayderOBJLoader obj_loader;
    NayderTextureSystem texture_engine;
    NayderMaterialSystem material_engine;

    // 1. Chaje modèl Blender yo
    CompiledMesh sniper_mesh = obj_loader.ParseOBJFile("Assets/Models/soldier.obj");
    CompiledMesh house_mesh = obj_loader.ParseOBJFile("Assets/Models/house.obj");

    // 2. Chaje Tèkstire yo
    TextureData weapon_tex = texture_engine.LoadTextureFromFile("Assets/Textures/soldier_skin.png");
    TextureData house_tex = texture_engine.LoadTextureFromFile("Assets/Textures/house_brick.jpg");

    // 3. Konstwi vrè Materyo Next-Gen yo ak bèl koyefisyan koutim yo!
    Material rifle_material = material_engine.CreateCustomMaterial("M4_Neon_Fall_Steel", 101, "METALLIC_WEAPON");
    Material wall_material = material_engine.CreateCustomMaterial("Abandond_House_Planks", 102, "ROUGH_WOOD");

    // 4. Aplike materyo yo sou Shader GPU a anlè sèn nan anvan draw call la kouri
    material_engine.ApplyMaterialToShader(rifle_material);
    material_engine.ApplyMaterialToShader(wall_material);

    std::cout << "\n🎬 [RASTER EXECUTION]: Swapping double frame-buffers with custom material passes..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
