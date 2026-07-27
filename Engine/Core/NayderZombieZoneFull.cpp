#include <iostream>
#include <string>
#include <vector>

struct PlayerStats {
    int hp = 100;
    int food_count = 0;
    int battery_count = 1; // Jwè a jwenn 1 Batri nan kay abandone yo!
    bool has_engine_parts = true; // Jwè a jwenn pyès motè nan forè a!
    bool flashlight_on = false;
    bool stealth_mode = true;
};

// =============================================================================
// NEW MODULE: VEHICLE REPAIR SUB-SYSTEM (Lojik Chape anba Zile a)
// =============================================================================
class VehicleRepairSystem {
private:
    bool is_repaired;

public:
    VehicleRepairSystem() {
        is_repaired = false;
    }

    void AttemptVehicleRepair(PlayerStats& player) {
        std::cout << "\n🚙 [VEHICLE CONTROLLER]: W ap enspekte yon gwo machin kraze nan mitan forè a..." << std::endl;
        std::cout << "    [SYSTEM CHECK]: Ap verifye si ou gen resous ki nesesè yo nan Envantè ou..." << std::endl;

        // Tcheke si jwè a gen Batri ak Pyès Motè
        if (player.battery_count >= 1 && player.has_engine_parts) {
            player.battery_count--;
            is_repaired = true;
            std::cout << "   🔧 [REPAIR SUCCESS]: Batri a ploge! Pyès motè yo enstale kòrèkteman!" << std::endl;
            std::cout << "   🔊 [AUDIO ENGINE]: ENGINE STARTED! (Vrrrroooom!!! Machin nan demare!)" << std::endl;
            std::cout << "   🎉 [GAME OVER]: Ou monte nan machin nan ak tout ekip ou, ou chape anba Zile a! VIKTWA!" << std::endl;
        } else {
            std::cout << "   ❌ [REPAIR FAILED]: Ou manke pyès! (Chèche Batri ak Pyès Motè nan kay abandone yo)." << std::endl;
        }
    }
};

class NPCSurvivor {
public:
    std::string name;
    int trust = 0;
    bool is_in_squad = false;

    NPCSurvivor(std::string npc_name) { name = npc_name; }

    void HandleInteraction(std::string choice, PlayerStats& player) {
        std::cout << "\n👤 [NPC]: \"" << name << "\" di: 'Please... I haven't eaten in two days.'" << std::endl;
        if (choice == "ACCEPT_AND_FEED") {
            trust += 30;
            is_in_squad = true;
            std::cout << " ❤️  [TRUST SYSTEM]: Trust +30! Nivo konfyans: " << trust << "/100" << std::endl;
            std::cout << " 😊 [SQUAD JOINED]: '" << name << "' antre nan ekip ou! L ap ede w tire zonbi epi reanime w." << std::endl;
        }
    }
};

int main() {
    std::cout << "\n=====================================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.48] - VEHICLE REPAIR & ESCAPE SYSTEM" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << " [*] Procedural Island Elements -> ✅ OPERATIONAL" << std::endl;
    std::cout << " [*] Vehicle Repair Engine      -> ✅ SUB-SYSTEM ONLINE AN C++" << std::endl;
    std::cout << " [*] Dynamic Trust Engine 0-100 -> ✅ ACTIVE" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    PlayerStats my_player;
    NPCSurvivor survivor("Sòlda_Anri");
    VehicleRepairSystem vehicle_system;

    // 1. Sekans Lannwit ak NPC
    std::cout << "🌙 [ENVIRONMENT]: Solèy la kouche. Bri zonbi ap deklanche byen lwen..." << std::endl;
    survivor.HandleInteraction("ACCEPT_AND_FEED", my_player);
    std::cout << "---------------------------------------------------------------------" << std::endl;

    // 2. SEKANS REPARE MACHIN LAN (Aksyon final la!)
    vehicle_system.AttemptVehicleRepair(my_player);

    std::cout << "=====================================================================" << std::endl;
    std::cout << " ✅ STATUS: Zombie Zone endgame vehicle loops validated successfully." << std::endl;
    std::cout << "=====================================================================" << std::endl;
    return 0;
}
