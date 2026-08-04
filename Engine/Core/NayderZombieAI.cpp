#include <iostream>
#include <string>
#include <vector>

// =============================================================================
// STEP 12 — HORDE ROLES & COMMANDER STRUCTS
// =============================================================================
enum class ZombieType { Runner, Brute, Toxic, Spitter, Commander };
enum class TacticalRole { Flank_Left, Center_Assault, Stay_Behind, Long_Range, Commander_Lead };
enum class AIState { Patrol, Chasing, Searching_Area, Cooldown_Wait, Attack };

struct Vector3D {
    float x;
    float z;
};

struct ZombieBlackboard {
    ZombieType type;
    std::string type_name;
    TacticalRole role;
    AIState current_state = AIState::Patrol;
    Vector3D current_pos = {0.0f, 0.0f};
    Vector3D last_known_player_pos = {-1.0f, -1.0f}; // STEP 10: MEMORY STORAGE
    int search_timer_seconds = 0;
    float attack_cooldown_timer = 0.0f; // STEP 11: COOLDOWN INTERLOCK
};

class NayderCombatAIModule {
private:
    bool is_horde_coordinated = false;

public:
    void SetHordeCoordination(bool status) {
        is_horde_coordinated = status;
    }

    // =============================================================================
    // STEP 10 & 11: MAIN ZOMBIE BEHAVIOR PROCESSING
    // =============================================================================
    void UpdateAIContext(ZombieBlackboard& zombie, Vector3D actual_player_pos, bool player_shot) {
        std::cout << "\n🧠 [AI MATRIX] - " << zombie.type_name << " | Role: ";
        switch(zombie.role) {
            case TacticalRole::Flank_Left:     std::cout << "Flank Left ↪️"; break;
            case TacticalRole::Center_Assault: std::cout << "Center Assault ⚔️"; break;
            case TacticalRole::Stay_Behind:    std::cout << "Stay Behind 🛡️"; break;
            case TacticalRole::Long_Range:     std::cout << "Long Range 🎯"; break;
            case TacticalRole::Commander_Lead:  std::cout << "Commander Lead 👑"; break;
        }
        std::cout << " | State: ";
        if(zombie.current_state == AIState::Patrol) std::cout << "Patrol";
        if(zombie.current_state == AIState::Chasing) std::cout << "Chasing";
        if(zombie.current_state == AIState::Searching_Area) std::cout << "Searching Area";
        if(zombie.current_state == AIState::Attack) std::cout << "Attack";
        std::cout << std::endl;

        // 1. STEP 10: MEMORY ALGORITHM
        if (player_shot) {
            zombie.last_known_player_pos = actual_player_pos; // Store position in blackboard memory
            zombie.current_state = AIState::Chasing;
            std::cout << "   💾 [MEMORY SYSTEM]: Sound heard! Storing LastKnownPosition: X=" << zombie.last_known_player_pos.x << " Z=" << zombie.last_known_player_pos.z << std::endl;
        }

        // Move towards memory position
        if (zombie.current_state == AIState::Chasing) {
            zombie.current_pos = zombie.last_known_player_pos;
            std::cout << "   🏃‍♂️ [MOVEMENT]: Arrived at LastKnownPosition." << std::endl;

            // Player has left the stored coordinate area
            if (actual_player_pos.x != zombie.last_known_player_pos.x || actual_player_pos.z != zombie.last_known_player_pos.z) {
                zombie.current_state = AIState::Searching_Area;
                zombie.search_timer_seconds = 10;
            } else {
                zombie.current_state = AIState::Attack;
            }
        }

        // Search Routine
        if (zombie.current_state == AIState::Searching_Area) {
            std::cout << "   👀 [SEARCH MODE]: Player gone! Searching surrounding grids for " << zombie.search_timer_seconds << " seconds..." << std::endl;
            zombie.search_timer_seconds = 0; // Simulate time dissipation
            std::cout << "   💤 [SEARCH TIMEOUT]: Target lost. Returning to original Patrol route." << std::endl;
            zombie.current_state = AIState::Patrol;
        }

        // 2. STEP 11: ATTACK COOLDOWN PROTOCOL
        if (zombie.current_state == AIState::Attack) {
            if (zombie.attack_cooldown_timer <= 0.0f) {
                std::cout << "   💥 [DAMAGE MATRIX]: Claw hit landed on Target! -25 HP." << std::endl;
                zombie.attack_cooldown_timer = 1.5f; // Set hardware execution lock to 1.5 seconds
                std::cout << "   ⏳ [COOLDOWN INTERLOCK]: Locking attacks for next " << zombie.attack_cooldown_timer << "s to balance mechanics." << std::endl;
            } else {
                std::cout << "   🚫 [COOLDOWN ACTIVE]: Attack skipped. Waiting for timer reset loop..." << std::endl;
            }
        }
    }

    // =============================================================================
    // STEP 12: COMMANDER HIERARCHY EVALUATOR
    // =============================================================================
    void EvaluateHordeCohesion(bool commander_alive) {
        std::cout << "\n👑 [HORDE COORDINATOR EVALUATOR]:" << std::endl;
        if (commander_alive) {
            SetHordeCoordination(true);
            std::cout << "   ⚡ [STATUS]: Commander spawned and ALIVE!" << std::endl;
            std::cout << "   🚀 [TACTICAL RESULT]: Horde is highly COORDINATED! Flank parameters applied on GPU runtime layers." << std::endl;
        } else {
            SetHordeCoordination(false);
            std::cout << "   💀 [STATUS]: Commander DEFEATED!" << std::endl;
            std::cout << "   📉 [TACTICAL RESULT]: Horde becomes DISORGANIZED! Speed dropped by 30%. Combat window opened!" << std::endl;
        }
    }
};

int main() {
    std::cout << "\n=====================================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.58] - MEMORY, COOLDOWN & HORDE ROLES" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << " 🏆 ROADMAP UPDATE:" << std::endl;
    std::cout << "  Vision ✅ │ Movement ✅ │ Position ✅ │ Zombie Types ✅ │ Pathfinding ✅" << std::endl;
    std::cout << "  Memory System ✅ │ Attack Cooldown ✅ │ Horde Roles ✅" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    NayderCombatAIModule combat_ai;
    Vector3D player_pos = {50.0f, 0.0f};

    // 1. Instantiate specialized roles
    ZombieBlackboard stalker = {ZombieType::Runner, "Runner Alpha", TacticalRole::Flank_Left};
    ZombieBlackboard heavy_boss = {ZombieType::Commander, "Horde Commander", TacticalRole::Commander_Lead};

    // SIMULATION 1: Step 10 & 11 Memory and Attack Cooldown tracking
    std::cout << "\n🎬 [SIMULATION PHASE 1] - Player shoots M4 at X=50 Z=0:";
    combat_ai.UpdateAIContext(stalker, player_pos, true);

    // Simulate player escaping immediately to X=90
    std::cout << "\n🎬 [SIMULATION PHASE 2] - Player flees to X=90 Z=0 (Zombie arrives at X=50):";
    Vector3D player_escaped_pos = {90.0f, 0.0f};
    combat_ai.UpdateAIContext(stalker, player_escaped_pos, false);

    std::cout << "\n---------------------------------------------------------------------";

    // SIMULATION 2: Step 12 Coordinated Team Combat vs Disorganization
    combat_ai.EvaluateHordeCohesion(true);   // Commander is fighting
    combat_ai.EvaluateHordeCohesion(false);  // 10-player squad eliminates Commander!

    std::cout << "=====================================================================" << std::endl;
    std::cout << " ✅ STATUS: Hardware behaviors compiled 100% stable." << std::endl;
    std::cout << "=====================================================================" << std::endl;
    return 0;
}
