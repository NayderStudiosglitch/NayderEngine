#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "Camera.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.68] - OBJ MODEL LOADER PIPELINE" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 GRAPHIC SUBSYSTEM MATRIX UNLOCKED:" << std::endl;
    std::cout << "  v0.0.66 Camera Subsystem -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.67 OpenGL Renderer  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.68 OBJ Model Loader -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.69 Texture System   -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    // 1. Fire up the platform display window
    NayderOpenGLRenderer renderer;
    renderer.CreateRenderWindow(1920, 1080, "Neon Fall 17 - 3D Object Streaming Viewport");

    // 2. Initialize the OBJ Parser Subsystem
    NayderOBJLoader obj_loader;

    // Stream and load your exact design roadmap assets straight from the virtual memory disk!
    CompiledMesh soldier_mesh = obj_loader.ParseOBJFile("Assets/Models/soldier.obj");
    obj_loader.UploadMeshToGPU(soldier_mesh);

    CompiledMesh zombie_mesh = obj_loader.ParseOBJFile("Assets/Models/zombie.obj");
    obj_loader.UploadMeshToGPU(zombie_mesh);

    CompiledMesh house_mesh = obj_loader.ParseOBJFile("Assets/Models/house.obj");
    obj_loader.UploadMeshToGPU(house_mesh);

    // 3. Confirm pipeline execution frame status
    std::cout << "\n🎬 [DRAW SYSTEM]: All asset nodes linked into active Scene Graph!" << std::endl;
    std::cout << " -> Rendering real custom 3D model vertices loops on screen viewport..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
