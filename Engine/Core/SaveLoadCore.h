#pragma once
#include <string>

struct GameSaveStateNode {
    int survival_day;
    int player_hp;
    int player_armor;
    int current_ammo;
    int reserve_ammo;
    int total_zombies_killed;
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
