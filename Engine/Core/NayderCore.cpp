#include <iostream>
#include <string>
#include <map>
#include <algorithm>

struct PlayerProfile {
    std::string name;
    int level;
    int weapons_unlocked;
    int ai_build_count_today;
    std::string language_code; // "ht", "en", elatriye
};

class NayderAdvancedGameRules {
private:
    std::map<std::string, std::string> npc_limit_messages;

public:
    NayderAdvancedGameRules() {
        // Tradiksyon mesaj blokus la pou NPC a nan lang natif natal yo
        npc_limit_messages["ht"] = "Hé zanmi, ou rive nan limit ou pou jodi a! Eseye ankò pita, demen, oswa nan 4 jou.";
        npc_limit_messages["en"] = "Hey friend, you reached your limit today! Try again later, tomorrow, or in 4 days.";
        npc_limit_messages["zh"] = "嘿朋友，你今天的次数已达上限！请稍后再试、明天或4天后再试。";
        npc_limit_messages["kp"] = "동무여, 오늘의 한계를 초과하였다! 나중에, 내일, 혹은 4일후에 다시 시도하라.";
    }

    void CheckPlayerLevelProgression(PlayerProfile& player) {
        std::cout << "\n📈 [PROGRESSION SYSTEM]: Ap verifye nivo '" << player.name << "' (Max: 200)..." << std::endl;
        
        if (player.level >= 60) {
            player.weapons_unlocked = 60;
            std::cout << " 🎉 [LEVEL 60 REACHED]: Tout 60 zam yo debloke otomatikman nan Loadout la! (" << player.weapons_unlocked << "/60 Weapons Active)" << std::endl;
        } else {
            std::cout << "    [STATUS]: Nivo " << player.level << "/200. Kontinye jwe pou w rive nan Level 60 pou debloke tout zam yo." << std::endl;
        }
    }

    void RequestAIWeaponBuild(PlayerProfile& player, std::string weapon_request) {
        std::cout << "\n🛠️  [AI BUILD REQUEST]: Mande bati: \"" << weapon_request << "\"" << std::endl;
        
        // Ogmante kantite kreyasyon yo
        player.ai_build_count_today++;
        std::cout << "    [COUNTER]: Kreyasyon jodi a: " << player.ai_build_count_today << "/3 fwa." << std::endl;

        // Si se 4tyèm fwa a, blokus deklanche
        if (player.ai_build_count_today > 3) {
            std::cout << "\n🚫 [AI LOCKOUT ACTIVATED]: Limit kreyasyon an depase!" << std::endl;
            
            // SIMULASYON ANIMASYON BOUCH NPC (Lipsync Bone Matrix)
            std::cout << " 🎭 [LIPSYNC ENGINE]: Activating facial skeletal joints for NPC model..." << std::endl;
            std::cout << "    [BOUCH ANIMATION]: Open/Close matrix calculating bone weight for speech tracking." << std::endl;
            
            // NPC a pale nan lang pa moun nan dirèkteman
            std::string msg = npc_limit_messages[player.language_code];
            if (msg.empty()) msg = npc_limit_messages["en"]; // Fallback on English
            
            std::cout << " 🤖 [NPC AI TALKING]: \"" << msg << "\"" << std::endl;
        } else {
            std::cout << " ✅ [AI SUCCESS]: Zam nan bati epi li pare nan VRAM." << std::endl;
        }
    }
};

class NayderEngineCPP {
private:
    NayderAdvancedGameRules rules_engine;

public:
    NayderEngineCPP() {
        std::cout << "\n=======================================================" << std::endl;
        std::cout << "     [NAYDER ENGINE v0.0.28] - GAME RULES & LIPSYNC CORE" << std::endl;
        std::cout << "=======================================================" << std::endl;
        std::cout << " [*] Level 200 Ceiling   -> ✅ CALIBRATED" << std::endl;
        std::cout << " [*] AI Usage Throttle   -> ✅ SAFETY HARDWARE LOCK ACTIVE" << std::endl;
        std::cout << " [*] Lipsync Bone Matrix -> ✅ COMPILING VIS_EME SHADERS" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
    }

    void RunSimulation() {
        // Kreye yon jwè tès ki nan Level 60 epi ki pale Kreyòl (HT)
        PlayerProfile my_player = {"Nayder_Dev_01", 60, 0, 0, "ht"};
        
        // 1. Tcheke nivo a pou debloke 60 zam yo
        rules_engine.CheckPlayerLevelProgression(my_player);
        std::cout << "-------------------------------------------------------" << std::endl;

        // 2. Jwè a mande bati zam 1ye fwa, 2yèm fwa, 3yèm fwa (Mache pafè)
        rules_engine.RequestAIWeaponBuild(my_player, "Build me a fast SMG");
        rules_engine.RequestAIWeaponBuild(my_player, "Build me a sniper blue, black color");
        rules_engine.RequestAIWeaponBuild(my_player, "Build me a shotgun");
        
        // 3. 4tyèm fwa! Blokus la deklanche epi NPC a ap kòmanse bouje bouch li an Kreyòl!
        rules_engine.RequestAIWeaponBuild(my_player, "Build me another rifle");
    }
};

int main() {
    NayderEngineCPP engine;
    engine.RunSimulation();
    return 0;
}
