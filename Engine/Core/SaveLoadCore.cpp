#include "SaveLoadCore.h"
#include <iostream>
#include <fstream>
NayderSaveLoadSystem::NayderSaveLoadSystem() {}
bool NayderSaveLoadSystem::SerializeSessionToDisk(const GameSaveStateNode& session_data) {
    std::cout << "\n💾 [SAVE CORE]: Serializing active memory..." << std::endl;
    std::ofstream write_stream("savegame.dat");
    if (!write_stream.is_open()) return false;
    write_stream << session_data.survival_day << "\n";
    write_stream << session_data.player_hp << "\n";
    write_stream << session_data.player_armor << "\n";
    write_stream << session_data.current_ammo << "\n";
    write_stream << session_data.reserve_ammo << "\n";
    write_stream << session_data.total_zombies_killed << "\n";
    write_stream << session_data.active_world_map << "\n";
    write_stream.close();
    std::cout << "   ✅ [DISK FLUSH]: savegame.dat synchronized into storage caches." << std::endl;
    return true;
}
bool NayderSaveLoadSystem::DeserializeSessionFromDisk(GameSaveStateNode& outbound_data) {
    std::cout << "\n📂 [LOAD CORE]: Restoring memory pointers..." << std::endl;
    std::ifstream read_stream("savegame.dat");
    if (!read_stream.is_open()) return false;
    read_stream >> outbound_data.survival_day;
    read_stream >> outbound_data.player_hp;
    read_stream >> outbound_data.player_armor;
    read_stream >> outbound_data.current_ammo;
    read_stream >> outbound_data.reserve_ammo;
    read_stream >> outbound_data.total_zombies_killed;
    read_stream >> outbound_data.active_world_map;
    read_stream.close();
    std::cout << "   ✅ [STATE RESTORED]: Game reverted back to: Day " << outbound_data.survival_day << std::endl;
    return true;
}
