#include "ZombieAI.h"
#include <iostream>
#include <cmath>

NayderZombieAIEngine::NayderZombieAIEngine() {}

void NayderZombieAIEngine::ProcessHordePathfindingTick(std::vector<ZombieEntityNode>& horde, float player_target_x, float delta_time) {
    for (auto& zombie : horde) {
        // Calculate direct 1D distance metric along the active X axis loop
        float distance_to_squad = std::abs(zombie.pos_x - player_target_x);

        // 1. STATE MACHINE EVALUATOR
        if (distance_to_squad <= attack_range_threshold) {
            zombie.current_state = AIState::ATTACK_LOCKED;
        } else if (distance_to_squad < 35.0f) {
            zombie.current_state = AIState::CHASING_PLAYER;
        } else {
            zombie.current_state = AIState::IDLE_PATROL;
        }

        // 2. VECTOR TRANSLATION STEP (CHASING LOGIC)
        if (zombie.current_state == AIState::CHASING_PLAYER) {
            // Determine direction vector to move toward the player player coordinate
            float move_direction = (player_target_x > zombie.pos_x) ? 1.0f : -1.0f;
            
            // Adjust coordinates scaled seamlessly via Delta Time parameters
            zombie.pos_x += move_direction * zombie.current_speed * delta_time;
            
            std::cout << "  ├── 🧟 [AI PATHFINDING]: Zombie_0" << zombie.unique_id << " [" << zombie.type_tag 
                      << "] chasing player -> New Position X: " << zombie.pos_x << " │ Dist: " << distance_to_squad << "m" << std::endl;
        }
        else if (zombie.current_state == AIState::ATTACK_LOCKED) {
            std::cout << "  ├── 💥 [AI ATTACK LAYER]: Zombie_0" << zombie.unique_id << " [" << zombie.type_tag 
                      << "] in target range! Biting player for -" << zombie.attack_damage << " HP dega!" << std::endl;
        }
    }
}
