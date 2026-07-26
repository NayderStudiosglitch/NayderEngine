#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

// Estrikti pou pwofil jwè a
struct PlayerProfile {
    std::string name;
    std::string nationality; // "HT", "USA", "ZH", "KP", elatriye
};

class NayderIntelligentLocalization {
private:
    std::map<std::string, std::string> lang_names;
    std::map<std::string, std::string> npc_voices;

public:
    NayderIntelligentLocalization() {
        // Map Kòd ak Non Lang yo
        lang_names["ht"] = "Haitian Creole (Kreyòl Ayisyen)";
        lang_names["en"] = "English (US/UK)";
        lang_names["fr"] = "French (Français)";
        lang_names["es"] = "Spanish (Español)";
        lang_names["pt"] = "Portuguese (Português)";
        lang_names["ru"] = "Russian (Русский)";
        lang_names["zh"] = "Chinese (中文)";
        lang_names["kp"] = "North Korean (조선말)";

        // Tradiksyon vwa NPC yo pou chak nasyon
        npc_voices["ht"] = "Sòlda, lènmi yo ap pwoche nan Ruins yo! Pare zam ou!";
        npc_voices["en"] = "Soldier, enemies are closing in on the Ruins! Ready your weapon!";
        npc_voices["zh"] = "士兵，敌人正向废墟逼近！准备好你的武器！";
        npc_voices["kp"] = "전사여, 원쑤들이 기지로 몰려온다! 무기를 잡으라!";
    }

    void SortBuildWeaponMenu(std::string nationality) {
        std::string primary_code = "en"; // Default
        
        // Detekte ki lang ki dwe premye selon nasyon an
        if (nationality == "HT") primary_code = "ht";
        else if (nationality == "USA") primary_code = "en";
        else if (nationality == "ZH") primary_code = "zh";
        else if (nationality == "KP") primary_code = "kp";

        std::cout << "\n🛠️  [BUILD WEAPON UI SORTING] - Nasyonalite detekte: " << nationality << std::endl;
        std::cout << " 🔥 PRIYORITE 1: " << lang_names[primary_code] << " ap parèt an premye nèt!" << std::endl;
        std::cout << " -------------------------------------------------------" << std::endl;
        std::cout << " > LÒT LANG KI DISPONIB ANBA L (6 LANG RESE YO):" << std::endl;

        // Afiche 6 lòt lang yo anba dousman san repete premye a
        for (auto const& [code, name] : lang_names) {
            if (code != primary_code) {
                std::cout << "   [-] " << name << std::endl;
            }
        }
    }

    void DynamicNPCSpeech(PlayerProfile player) {
        std::string lang_code = "en"; // Default
        
        // Adaptasyon lang NPC a an tan reyèl selon jwè a
        if (player.nationality == "HT") lang_code = "ht";
        else if (player.nationality == "USA") lang_code = "en";
        else if (player.nationality == "ZH") lang_code = "zh";
        else if (player.nationality == "KP") lang_code = "kp";

        std::cout << "\n🗣️  [NPC DYNAMIC VOICE CHAT]: Jwè '" << player.name << "' gen nasyonalite " << player.nationality << std::endl;
        std::cout << " 🤖 [NPC AI VOICE]: \"" << npc_voices[lang_code] << "\"" << std::endl;
    }
};

class NayderEngineCPP {
private:
    NayderIntelligentLocalization intel_local;

public:
    NayderEngineCPP() {
        std::cout << "\n=======================================================" << std::endl;
        std::cout << "     [NAYDER ENGINE v0.0.27] - INTENTIONAL AI LOCALIZATION" << std::endl;
        std::cout << "=======================================================" << std::endl;
        std::cout << " [*] Context IP Detection -> ✅ ONLINE" << std::endl;
        std::cout << " [*] Dynamic UI Sorting   -> ✅ GRADIENT ACTIVE" << std::endl;
        std::cout << " [*] Adaptive NPC Voice   -> ✅ SATELLITE MATRIX SYNCED" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
    }

    void RunSimulation() {
        // TÈS 1: Jwè ki soti AYITI (HT)
        PlayerProfile player1 = {"Nayder_Haiti_01", "HT"};
        intel_local.SortBuildWeaponMenu(player1.nationality);
        intel_local.DynamicNPCSpeech(player1);
        
        std::cout << "\n=======================================================" << std::endl;

        // TÈS 2: Jwè ki soti USA
        PlayerProfile player2 = {"John_USA_99", "USA"};
        intel_local.SortBuildWeaponMenu(player2.nationality);
        intel_local.DynamicNPCSpeech(player2);
    }
};

int main() {
    NayderEngineCPP engine;
    engine.RunSimulation();
    return 0;
}
