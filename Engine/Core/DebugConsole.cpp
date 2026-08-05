#include "DebugConsole.h"
#include <iostream>

NayderDebugConsole::NayderDebugConsole() {}

void NayderDebugConsole::ExecuteDebugCommand(std::string command, int& out_hp, int& out_ammo, bool& out_horde_trigger) {
    std::cout << "\n🛠️  [RUNTIME DEBUG CONSOLE]: Processing command string -> \"" << command << "\"" << std::endl;

    if (command == "god_mode") {
        out_hp = 99999;
        std::cout << "   🚀 [CHEAT ENABLED]: GOD_MODE STATUS: ON! Player HP locked at max safety parameters." << std::endl;
    } 
    else if (command == "give_ammo") {
        out_ammo = 180;
        std::cout << "   🔫 [CHEAT ENABLED]: GIVE_AMMO! Magazine arrays filled up to: 30 / " << out_ammo << " rounds." << std::endl;
    } 
    else if (command == "spawn_horde") {
        out_horde_trigger = true;
        std::cout << "   ⚠️  [DEBUG EVENT]: SPAWN_HORDE! Injecting 50 dynamic runner assets into active Scene Graph slots!" << std::endl;
    } 
    else {
        std::cout << "   ❌ [CONSOLE ERROR]: Unknown command token. Use: [god_mode, give_ammo, spawn_horde]" << std::endl;
    }
}
