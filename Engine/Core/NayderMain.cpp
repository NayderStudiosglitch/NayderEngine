#include "AssetManager.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.97] - ASSET MANAGER RUNTIME" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 ROADMAP STATUS UPDATE:" << std::endl;
    std::cout << "  v0.0.96 Asset Manager Runtime  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.97 Resource Hot Reload    -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.98 Save/Load Game System  -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // Kounye a kòd C++ ou te vle kouri a pral kouri pafè andedan motè a!
    NayderAssetManagerRuntime assets;
    
    // Chaje Modèl yo
    assets.LoadModel("Assets/Models/soldier.obj");
    assets.LoadModel("Assets/Models/zombie.obj");
    
    // Chaje Tèkstire yo
    assets.LoadTexture("Assets/Textures/soldier.png");
    assets.LoadTexture("Assets/Textures/zombie.png");
    
    // Chaje Odyo yo
    assets.LoadSound("Assets/Audio/M4.wav");
    assets.LoadSound("Assets/Audio/Zombie.wav");

    // Tès sistèm Hot Reload v0.0.97 la!
    assets.ExecuteResourceHotReload();

    // Afiche Statistik yo
    assets.PrintStatistics();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
