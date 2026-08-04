#include <iostream>
#include <string>

class NPCCooperationModule {
public:
    void SimulateNPCOrchestration(std::string event_trigger) {
        std::cout << "\n👥 [NPC COOPERATION LOOP - STABLE]:" << std::endl;
        if (event_trigger == "SOLDIER_FIRE") {
            std::cout << " 💥 [NPC_SOLDIER]: Sees Zombie! -> Shooting weapons!" << std::endl;
            std::cout << " 🧟 [HORDE SENSORS]: Nearby Zombies hear the gunshot and chase!" << std::endl;
            std::cout << " 🩹 [NPC_DOCTOR]: Evading danger -> Hiding in defensive loop." << std::endl;
        }
    }
};
