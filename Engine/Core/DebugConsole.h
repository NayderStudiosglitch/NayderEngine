#pragma once
#include <string>

class NayderDebugConsole {
public:
    NayderDebugConsole();
    void ExecuteDebugCommand(std::string command, int& out_hp, int& out_ammo, bool& out_horde_trigger);
};
