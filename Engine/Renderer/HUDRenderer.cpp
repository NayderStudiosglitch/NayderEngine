#include "HUDRenderer.h"
#include <iostream>

NayderHUDRenderer::NayderHUDRenderer() {}

void NayderHUDRenderer::SetOrthographicProjection() {
    // Overriding projection parameters to 2D Screen Space bypassing 3D depth buffers
    std::cout << "\n🎛️  [HUD RENDER MATRIX]: Overriding projection parameters to 2D Orthographic Mode..." << std::endl;
}

void NayderHUDRenderer::RenderHUDDashboard(const HUDLiveStats& stats) {
    // Calculate the absolute viewport center for the crosshair layout
    int center_x = 1366 / 2;
    int center_y = 768 / 2;

    std::cout << "📺 [HUD DASHBOARD REPLICATION]: Printing live screen interface layout arrays..." << std::endl;
    std::cout << " +----------------------------------------------------------------------+" << std::endl;
    std::cout << " |  FPS: " << stats.current_fps << " Lock (BOULE LWEN)  │  OBJECTIVE: " << stats.objective << "  |" << std::endl;
    std::cout << " +----------------------------------------------------------------------+" << std::endl;
    
    // Compute HP visual block increments
    std::cout << " |  HP    : [";
    int hp_blocks = stats.current_hp / 10;
    for (int i = 0; i < 12; ++i) { if (i < hp_blocks) std::cout << "█"; else std::cout << "░"; }
    std::cout << "] " << stats.current_hp << " / " << stats.max_hp << " HP                          |" << std::endl;

    // Compute Armor visual block increments
    std::cout << " |  ARMOR : [";
    int armor_blocks = stats.current_armor / 10;
    for (int i = 0; i < 10; ++i) { if (i < armor_blocks) std::cout << "█"; else std::cout << "░"; }
    std::cout << "] " << stats.current_armor << " / " << stats.max_armor << " AR                          |" << std::endl;

    std::cout << " +----------------------------------------------------------------------+" << std::endl;
    std::cout << " |  AMMO  : " << stats.clip_ammo << " / " << stats.reserve_ammo << " (AUTO)   │  ZOMBIES ELIMINATED: x" << stats.total_kills << "            |" << std::endl;
    std::cout << " +----------------------------------------------------------------------+" << std::endl;

    // v0.1.6 CENTRAL COMBAT CROSSHAIR CALCULATOR
    std::cout << "\n🎯 [CROSSHAIR SYSTEM - v0.1.6]:" << std::endl;
    std::cout << " ├── Viewport Midpoint Node Locked at Coordinate: (" << center_x << ", " << center_y << ")" << std::endl;
    std::cout << " └── Raycast Target Crosshair Projected ->      [ + ]" << std::endl;
}

void NayderHUDRenderer::RestorePerspectiveProjection() {
    std::cout << "🔄 [HUD RENDER MATRIX]: Popping 2D frames. Perspective depth buffers restored." << std::endl;
}
