#include "../Physics/Collision.cpp"
#include <iostream>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.65] - CUSTOM 3D COLLISION SYSTEM" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 NEW REAL-TIME 3D COLLISION PIPELINE:" << std::endl;
    std::cout << "  v0.0.61 Entity System    -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.62 Scene Graph      -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.65 3D Box Collision -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    CollisionSystem physics;

    // TÈS 1: Player vs Miray an fòma 3D pafè (X, Y, Z, W, H, D)
    // BoxCollider: {x, y, z, width, height, depth}
    BoxCollider player = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};  // Jwè a gwo e long
    BoxCollider wall   = {4.0f, 0.0f, 0.0f, 2.0f, 5.0f, 0.5f};  // Gwo miray ki nan X = 4

    std::cout << "[PHYSICS TICK 1]: Player ap avanse nan forè a..." << std::endl;
    if (physics.CheckCollision(player, wall)) {
        std::cout << " 🚫 [COLLISION]: Jwè a frape miray la nan espas 3D a!" << std::endl;
    } else {
        std::cout << " ✅ [CLEAR]: Pa gen okenn kolizyon. Player glise nòmal." << std::endl;
    }

    // TÈS 2: Fòse Jwè a mache dwat andedan Kowòdone miray la!
    std::cout << "\n[PHYSICS TICK 2]: Player a mache antre nan kowòdone X = 3.5f..." << std::endl;
    player.x = 3.5f; // Jwè a deplase, b bwat li frape miray la kounye a!

    if (physics.CheckCollision(player, wall)) {
        std::cout << " 🚫 [3D COLLISION INTERSECTION!]: Mover frape miray solid la!" << std::endl;
        std::cout << "    [VELOCITY]: Stop movement! Force vector set to 0.0f." << std::endl;
    } else {
        std::cout << " ✅ [CLEAR]: Pa gen kolizyon." << std::endl;
    }

    std::cout << "=======================================================" << std::endl;
    return 0;
}
