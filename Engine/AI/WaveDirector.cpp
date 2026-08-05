#include "WaveDirector.h"
#include "../AI/ZombieAI.h"
#include <iostream>
NayderWaveDirector::NayderWaveDirector() {}
void NayderWaveDirector::InitializeNewWave(WaveConfig& config, std::vector<ZombieEntityNode>& horde) {
    config.current_wave++;
    config.total_zombies_this_wave = config.current_wave * 4;
    config.remaining_alive_zombies = config.total_zombies_this_wave;
    config.wave_in_progress = true;
    config.next_wave_cooldown = 0.0f;
    float scaled_speed = base_zombie_speed * (1.0f + (config.current_wave * 0.15f));
    horde.clear();
    std::cout << "\n🚨 [WAVE DIRECTOR]: Wave " << config.current_wave << " started! Spawning " << config.total_zombies_this_wave << " runners." << std::endl;
    for (int i = 1; i <= config.total_zombies_this_wave; ++i) {
        ZombieEntityNode z;
        z.unique_id = i;
        z.type_tag = "Wave_Runner";
        z.pos_x = 15.0f + (i * 3.0f);
        z.current_speed = scaled_speed;
        z.attack_damage = 10 + config.current_wave;
        z.current_state = AIState::IDLE_PATROL;
        horde.push_back(z);
    }
}
void NayderWaveDirector::EvaluateBarricadeIntersections(BarricadeNode& wall, float zombie_x, int attack_damage, float delta_time) {
    if (wall.is_destroyed) return;
    if (zombie_x <= wall.pos_x + 1.0f && zombie_x >= wall.pos_x - 1.0f) {
        wall.current_durability -= attack_damage;
        if (wall.current_durability <= 0) {
            wall.current_durability = 0;
            wall.is_destroyed = true;
            std::cout << " 🧱 [BARRICADE COLLAPSED]: Sandbag gate breached!" << std::endl;
        }
    }
}
void NayderWaveDirector::EvaluateWaveVictoryConditions(WaveConfig& config, int current_kills) {
    if (!config.wave_in_progress) return;
    if (current_kills >= config.total_zombies_this_wave) {
        config.wave_in_progress = false;
        config.next_wave_cooldown = 5.0f;
    }
}
