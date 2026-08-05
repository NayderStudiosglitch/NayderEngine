#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "../Renderer/Terrain.cpp"
#include "../Renderer/ParticleSystem.cpp"
#include "../Animation/Animation.cpp"
#include "../Audio/Audio.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.76] - INTEGRATED VFX MATRIX" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 NEW SYSTEM INTEGRATION ROADMAP UNLOCKED:" << std::endl;
    std::cout << "  v0.0.75 Spatial Audio    -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.76 Particle System  -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.77 UI/HUD Renderer  -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderParticleSystem vfx_engine;

    // Simulate Inter-module connection: Bullet hits Zombie (Combining modules v0.0.65 + v0.0.68 + v0.0.76)
    std::cout << "🎬 [COMBAT LOGIC TRIGGER]: Bullet Raycast collision intersection detected on Zombie Mesh node!" << std::endl;
    
    // 1. Spawn a precise directional blood splatter at the hitbox intersection coordinate
    vfx_engine.SpawnVFXEmitter(VFXType::BLOOD_IMPACT, 14.5f, 1.8f, 2.0f, 150);

    // 2. Spawn concrete wall sparks from weapon crossfire stray shots
    vfx_engine.SpawnVFXEmitter(VFXType::BULLET_IMPACT, -5.0f, 0.5f, 12.0f, 45);

    // 3. Simulate Day 100 Endgame Endgame aftermath - Deploying heavy volumetric nuclear fallout dust filters
    vfx_engine.SpawnVFXEmitter(VFXType::NUKE_DUST, 0.0f, 0.0f, 0.0f, 2000);

    // 4. Fire the updates and display sweeps over our GPU pipeline buffers
    vfx_engine.UpdateParticleLifeCycles(0.016f); // 16ms frame delta updates
    vfx_engine.RenderParticleBuffers();

    std::cout << "\n🎬 [SYSTEM DISPLAY MAP]: Flushing shader uniform matrices..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
