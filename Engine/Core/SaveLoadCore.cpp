#include "SaveLoadCore.h"
#include <iostream>
#include <fstream>

NayderSaveLoadSystem::NayderSaveLoadSystem() {}

bool NayderSaveLoadSystem::SerializeSessionToDisk(const GameSaveStateNode& session_data) {
    std::cout << "\n💾 [SAVE INTEGRATION ENGINE]: Gathering active runtime inventory arrays..." << std::endl;
    std::ofstream write_stream(storage_disk_file);
    if (!write_stream.is_open()) return false;

    // Stream packed tokens completely into localized file sectors
    write_stream << session_data.survival_day << "\n";
    write_stream << session_data.player_hp << "\n";
    write_stream << session_data.player_armor << "\n";
    write_stream << session_data.total_zombies_killed << "\n";
    write_stream << session_data.active_equipped_slot_index << "\n";
    write_stream << session_data.primary_m4_clip << "\n";
    write_stream << session_data.primary_m4_reserve << "\n";
    write_stream << session_data.secondary_pistol_clip << "\n";
    write_stream << session_data.secondary_pistol_reserve << "\n";
    write_stream << session_data.active_world_map << "\n";
    write_stream.close();

    std::cout << "   ✅ [DISK FLUSH COMPLETE]: savegame.dat updated with full multi-weapon loadout states!" << std::endl;
    return true;
}

bool NayderSaveLoadSystem::DeserializeSessionFromDisk(GameSaveStateNode& outbound_data) {
    std::cout << "\n📂 [LOAD INTEGRATION ENGINE]: Extracting serialized state maps..." << std::endl;
    std::ifstream read_stream(storage_disk_file);
    if (!read_stream.is_open()) return false;

    read_stream >> outbound_data.survival_day;
    read_stream >> outbound_data.player_hp;
    read_stream >> outbound_data.player_armor;
    read_stream >> outbound_data.total_zombies_killed;
    read_stream >> outbound_data.active_equipped_slot_index;
    read_stream >> outbound_data.primary_m4_clip;
    read_stream >> outbound_data.primary_m4_reserve;
    read_stream >> outbound_data.secondary_pistol_clip;
    read_stream >> outbound_data.secondary_pistol_reserve;
    read_stream >> outbound_data.active_world_map;
    read_stream.close();

    std::cout << "   ✅ [STATE RESTORED]: Re-aligned Backpack Slot #" << outbound_data.active_equipped_slot_index << " from data bounds." << std::endl;
    return true;
}
