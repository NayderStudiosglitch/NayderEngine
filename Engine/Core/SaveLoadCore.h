#pragma once
#include <string>

struct GameSaveStateNode {
    int survival_day;
    int player_hp;
    int player_armor;
    int total_zombies_killed;
    
    // v0.1.8 SPECIFIC EXTENDED INVENTORY STATE MARKERS
    int active_equipped_slot_index;
    int primary_m4_clip;
    int primary_m4_reserve;
    int secondary_pistol_clip;
    int secondary_pistol_reserve;
    
    std::string active_world_map;
};

class NayderSaveLoadSystem {
private:
    std::string storage_disk_file = "savegame.dat";

public:
    NayderSaveLoadSystem();
    bool SerializeSessionToDisk(const GameSaveStateNode& session_data);
    bool DeserializeSessionFromDisk(GameSaveStateNode& outbound_data);
};
