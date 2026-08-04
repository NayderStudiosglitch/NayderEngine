#include <iostream>
#include <string>
#include "../AI/ZombieCombat.cpp"
#include "../AI/NPCCooperation.cpp"

struct PlayerStealthState { bool is_crouching = false; bool flashlight_on = false; };

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "    [NAYDER ENGINE v0.0.60] - MODULAR ARCHITECTURE" << std::endl;
    std::cout << "=======================================================" << std::endl;

    ZombieBlackboard zombie;
    PlayerStealthState player = {true, true};

    // RANJE TYPO A VÈT KÒRÈKTÈMAN
    float base_vision = 50.0f * 2.5f * 0.4f;
    float base_hearing = 40.0f * 0.5f;
    std::cout << "👁️  [DETECTION SENSORS]: Vision: " << base_vision << "m | Hearing: " << base_hearing << "m" << std::endl;

    // RUN COMBAT MODULE
    ZombieCombatModule combat;
    combat.RegisterHitImpact(zombie, HitboxZone::Head, 25);
    combat.RegisterHitImpact(zombie, HitboxZone::Leg, 20);

    // RUN NPC COOPERATION MODULE (RANJE E KOURI NAN MENM FICHE A KOUNYEA!)
    NPCCooperationModule coop;
    coop.SimulateNPCOrchestration("SOLDIER_FIRE");

    std::cout << "=======================================================" << std::endl;
    return 0;
}
