#pragma once
#include <string>
#include <vector>

enum class AIState { IDLE_PATROL, CHASING_PLAYER, ATTACK_LOCKED };

struct ZombieEntityNode {
    unsigned int unique_id;
    std::string type_tag;
    float pos_x;
    float current_speed;
    int attack_damage;
    AIState current_state = AIState::IDLE_PATROL;
};

class NayderZombieAIEngine {
private:
    float attack_range_threshold = 1.8f;

public:
    NayderZombieAIEngine();
    void ProcessHordePathfindingTick(std::vector<ZombieEntityNode>& horde, float player_target_x, float delta_time);
};
