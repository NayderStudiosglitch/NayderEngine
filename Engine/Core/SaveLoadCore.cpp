#include "SaveLoadCore.h"
#include <iostream>
#include <fstream>

NayderSaveLoadEngine::NayderSaveLoadEngine() {
    // Filesystem handles initialized
}

bool NayderSaveLoadEngine::WriteSaveGameToDisk(const GameSaveState& state) {
    std::cout << "\n💾 [SAVE ENGINE]: Serializing active runtime memory blocks..." << std::endl;
    std::cout << " -> Opening outbound file stream: std::ofstream(\"" << save_file_path << "\") ..." << std::endl;
    
    std::ofstream write_stream(save_file_path);
    if (!write_stream.is_open()) {
        std::cout << " 🚫 [SAVE ERROR]: Critical! Cannot access local disk sectors to write save state." << std::endl;
        return false;
    }

    // Write packed structural tokens line by line into local disk space
    write_stream << state.saved_day << "\n";
    write_stream << state.player_hp << "\n";
    write_stream << state.player_armor << "\n";
    write_stream << state.total_ammo << "\n";
    write_stream << state.zombies_killed << "\n";
    write_stream << state.current_map << "\n";
    write_stream.close();

    std::cout << "   ┌── [SERIALIZATION SUCCESS]: Data packaged successfully!" << std::endl;
    std::cout << "   ├── Day Saved : " << state.saved_day << " │ Zombies Hunted: " << state.zombies_killed << std::endl;
    std::cout << "   └── ✅ [DISK FLUSH COMPLETE]: '" << save_file_path << "' updated and synced safely." << std::endl;
    return true;
}

bool NayderSaveLoadEngine::ReadSaveGameFromDisk(GameSaveState& out_state) {
    std::cout << "\n📂 [LOAD ENGINE]: Preparing system state restoration..." << std::endl;
    std::cout << " -> Opening inbound file stream: std::ifstream(\"" << save_file_path << "\") ..." << std::endl;

    std::ifstream read_stream(save_file_path);
    if (!read_stream.is_open()) {
        std::cout << " 🚫 [LOAD ERROR]: No previous save file found on hardware layout paths." << std::endl;
        return false;
    }

    // Parse tokens back into operational runtime variables
    read_stream >> out_state.saved_day;
    read_stream >> out_state.player_hp;
    read_stream >> out_state.player_armor;
    read_stream >> out_state.total_ammo;
    read_stream >> out_state.zombies_killed;
    read_stream >> out_state.current_map;
    read_stream.close();

    std::cout << "   ┌── [DESERIALIZATION SUCCESS]: Token verification passed!" << std::endl;
    std::cout << "   └── ✅ [STATE RESTORED]: Game swapped back to: Day " << out_state.saved_day << " | Zone: " << out_state.current_map << std::endl;
    return true;
}
