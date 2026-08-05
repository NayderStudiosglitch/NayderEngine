#pragma once
#include <string>

struct HUDPlayerStats {
    int hp = 100;
    int armor = 75;
    int current_ammo = 30;
    int reserve_ammo = 180;
    int grenades = 3;
    int fps_lock = 107;
    int network_ping = 18;
    std::string current_objective = "Reach Extraction Zone";
};

class NayderHUDRenderer {
private:
    int viewport_width = 1920;
    int viewport_height = 1080;

public:
    NayderHUDRenderer();
    void SetOrthographicProjection();
    void RenderHUDDashboard(const HUDPlayerStats& stats);
    void RestorePerspectiveProjection();
};
