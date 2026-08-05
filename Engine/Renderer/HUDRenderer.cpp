#include "HUDRenderer.h"
#include <iostream>
NayderHUDRenderer::NayderHUDRenderer() {}
void NayderHUDRenderer::SetOrthographicProjection() {
    std::cout << "\n[HUD ENGINE]: Matrix Mode Swapped to Orthographic." << std::endl;
    std::cout << " -> Switching GPU pipeline from 3D to Flat 2D Screen Space." << std::endl;
}
void NayderHUDRenderer::RenderHUDDashboard(const HUDPlayerStats& stats) {
    std::cout << "\n📺 [UI CANVAS RASTERIZER]: Rendering screen overlay components..." << std::endl;
    std::cout << " ┌─────────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << " │  SYSTEM COUNTER: [ FPS: " << stats.fps_lock << " ]  │  NETWORK NODE: [ PING: " << stats.network_ping << "ms ]              │" << std::endl;
    std::cout << " ┌─────────────────────────────────────────────────────────────────────────────┘" << std::endl;
    std::cout << "  [VITAL MATRIX - BOTTOM LEFT]:" << std::endl;
    std::cout << "   ├── HP BAR     : [██████████░░] " << stats.hp << " HP" << std::endl;
    std::cout << "   └── ARMOR BAR  : [████████░░░░] " << stats.armor << " AR" << std::endl;
    std::cout << "  [AMMO & EQUIPMENT - BOTTOM RIGHT]:" << std::endl;
    std::cout << "   ├── CLIP VALUE : " << stats.current_ammo << " / " << stats.reserve_ammo << " (AUTOMATIC)" << std::endl;
    std::cout << "   └── GRENADES   : x" << stats.grenades << " Frag Units" << std::endl;
    std::cout << "  [VIEWPORT SCREEN CENTER]:" << std::endl;
    std::cout << "   ├── CROSSHAIR  : Projected central target vector node: [+]" << std::endl;
    std::cout << "   ├── MINI-MAP   : Active radar box sampling world entities." << std::endl;
    std::cout << "   └── OBJECTIVE  : " << stats.current_objective << std::endl;
}
void NayderHUDRenderer::RestorePerspectiveProjection() {
    std::cout << "\n[HUD ENGINE]: Matrix Restoration -> 3D Viewport restored." << std::endl;
}
