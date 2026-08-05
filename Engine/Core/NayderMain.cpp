#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "../Renderer/Terrain.cpp"
#include "../Animation/Animation.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.74] - REAL-TIME SKELETAL ANIMATION" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 3D WORLD INTEGRATION ROADMAP UPDATE:" << std::endl;
    std::cout << "  v0.0.72 Shadow Mapping   -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.73 Terrain Renderer -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.74 Animation Engine -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.75 Audio Engine     -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderOBJLoader obj_loader;
    NayderAnimationEngine anim_engine;

    // Load geometry targets
    CompiledMesh zombie = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    CompiledMesh soldier = obj_loader.ParseOBJFile("Assets/Models/soldier.obj");

    // 1. Initialize character skeletal bone rigs
    anim_engine.ConfigureSkeletalRig(soldier.model_name, 64); // 64 Bone rig for complex player moves
    anim_engine.ConfigureSkeletalRig(zombie.model_name, 32);  // Optimized 32 Bone rig for fast horde counts

    // 2. Load and extract explicit animation clip parameters
    AnimationClip sprint = {"Zombie_Sprint_Loop", 30, 1.0f};
    AnimationClip hit_react = {"Zombie_Impact_Stumble", 45, 1.5f};
    
    anim_engine.RegisterAnimationClip(sprint);
    anim_engine.RegisterAnimationClip(hit_react);

    // 3. Simulate gameplay event: Player bullet registers on zombie leg -> Trigger Blending!
    anim_engine.BlendAnimationStates("Zombie_Sprint_Loop", "Zombie_Impact_Stumble", 0.35f);
    anim_engine.UpdateSkeletalShaderUniforms();

    std::cout << "\n🎬 [DISPLAY SYSTEM]: Swapping frame buffers with real-time hardware skeletal skinning loops..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
