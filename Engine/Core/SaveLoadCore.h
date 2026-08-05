#pragma once
#include <string>

struct GameSaveState {
    int saved_day;
    int player_hp;
    int player_armor;
    int total_ammo;
    int zombies_killed;
    std::string current_map;
};

class NayderSaveLoadEngine {
private:
    std::string save_file_path = "savegame.dat";

public:
    NayderSaveLoadEngine();
    bool WriteSaveGameToDisk(const GameSaveState& state);
    bool ReadSaveGameFromDisk(GameSaveState& out_state);
};
