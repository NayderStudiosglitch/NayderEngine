#include "AssetManager.cpp"
#include "SaveLoadCore.cpp"
#include "DebugConsole.cpp" // Interlocking real console components
#include <iostream>
#include <string>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.99] - RUNTIME CONSOLE DEBUG" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PHASE 5 RUNTIME COMPLETE! FINAL MATRIX UNLOCKED:" << std::endl;
    std::cout << "  v0.0.97 Resource Hot Reload    -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.98 Save/Load Game System  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.99 Runtime Console Debug  -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << " 👑 v0.1.0  FIRST PLAYABLE PROTOTYPE -> \342\226\220 NEXT (THE GRAND SLAM)" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderDebugConsole developer_console;

    // Estatistik Jwè a nan memwa RAM an tan reyèl
    int player_hp = 100;
    int player_ammo = 30;
    bool horde_alert = false;

    std::cout << "[INITIAL CORE STATS]: HP: " << player_hp << " │ Ammo Reserve: " << player_ammo << std::endl;

    // TÈS INTERAKTIF 1: Devlopè a tape 'god_mode'
    developer_console.ExecuteDebugCommand("god_mode", player_hp, player_ammo, horde_alert);

    // TÈS INTERAKTIF 2: Devlopè a tape 'give_ammo'
    developer_console.ExecuteDebugCommand("give_ammo", player_hp, player_ammo, horde_alert);

    // TÈS INTERAKTIF 3: Devlopè a tape 'spawn_horde'
    developer_console.ExecuteDebugCommand("spawn_horde", player_hp, player_ammo, horde_alert);

    std::cout << "\n📊 [UPDATED RUNTIME METRICS]:" << std::endl;
    std::cout << " ├── Player Health Status : " << player_hp << " HP" << std::endl;
    std::cout << " ├── Weapon Ammo Reserve  : " << player_ammo << " rounds" << std::endl;
    std::cout << " └── Horde Aggro Active   : " << (horde_alert ? "YES (50 Zombies chasing)" : "NO") << std::endl;

    std::cout << "=======================================================" << std::endl;
    return 0;
}
