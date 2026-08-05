#pragma once
#include <string>
#include <vector>

struct WaveConfig {
    int current_wave;
    int total_zombies_this_wave;
    int remaining_alive_zombies;
    bool wave_in_progress;
    float next_wave_cooldown;
};

struct BarricadeNode {
    std::string identity;
    float pos_x;
    int current_durability;
    int max_durability;
    bool is_destroyed;
};

class NayderWaveDirector {
private:
    float base_zombie_speed = 3.5f;

public:
    NayderWaveDirector();
    void InitializeNewWave(WaveConfig& config, std::vector<struct ZombieEntityNode>& horde);
    void EvaluateBarricadeIntersections(BarricadeNode& wall, float zombie_x, int attack_damage, float delta_time);
    void EvaluateWaveVictoryConditions(WaveConfig& config, int current_kills);
};
