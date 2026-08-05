#pragma once
#include <string>

struct HUDLiveStats {
    int current_hp;
    int max_hp;
    int current_armor;
    int max_armor;
    int clip_ammo;
    int max_clip;
    int reserve_ammo;
    int total_kills;
    int current_fps;
    std::string objective;
};

class NayderHUDRenderer {
public:
    NayderHUDRenderer();
    void SetOrthographicProjection();
    void RenderHUDDashboard(const HUDLiveStats& stats);
    void RestorePerspectiveProjection();
};
