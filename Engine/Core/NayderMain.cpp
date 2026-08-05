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
#include "../AI/NavMesh.cpp" // Linked modularly
#include "SaveLoadCore.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.81] - OPEN-WORLD NAVMESH CORE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 SYSTEM INTEGRATION PROGRESS MAP:" << std::endl;
    std::cout << "  v0.0.79 Asset Manager    -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.80 Animation Graph  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.81 Navigation Mesh  -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.82 Multiplayer Sync -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderNavMeshEngine nav_mesh_system;

    // 1. Bake the custom Navigation mesh grid directly over your 35x35 terrain topology bounds
    nav_mesh_system.BakeNavMeshFromHeightmap(35, 1.8f);

    // 2. Query physics/AI pathing constraints across different terrain sections
    float agent_speed = 5.0f;

    // SCENARIO A: Zombie Runner racing through a flat city road node
    std::cout << "\n[AI PATHFINDING EVALUATION 1]: Runner moving through open streets..." << std::endl;
    nav_mesh_system.QueryPathNodeConstraints(4.5f, 12.0f, -0.5f, 10.5f, agent_speed);

    // SCENARIO B: Zombie Brute tries to walk up an extremely steep mountain cliff side
    std::cout << "\n[AI PATHFINDING EVALUATION 2]: Brute attempts to shortcut over Alpha Cliff face..." << std::endl;
    float brute_speed = 3.0f;
    nav_mesh_system.QueryPathNodeConstraints(15.0f, 15.0f, 45.8f, 55.0f, brute_speed);

    // SCENARIO C: 10-Player Squad tactical team moving up a gentle perimeter ridge hill
    std::cout << "\n[AI PATHFINDING EVALUATION 3]: Player squad pushing up the exterior valley ridges..." << std::endl;
    float squad_speed = 6.0f;
    nav_mesh_system.QueryPathNodeConstraints(28.0f, 5.0f, 12.2f, 28.5f, squad_speed);

    std::cout << "\n🎬 [SYSTEM REPLICATION]: Swapping display frame buffers..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
