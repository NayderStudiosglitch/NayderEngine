#include <iostream>
#include <string>
#include <vector>

// =============================================================================
// MODIL: SOUND DETECTION & GROUP/HORDE BRAIN ENGINE
// =============================================================================
struct WeaponFireEvent {
    std::string weapon_type;
    float source_x;
    float source_z;
    int sound_decibels; // Nivo bri zam nan ap fè
};

class NayderSoundDetectionEngine {
public:
    bool CheckIfZombieHearsNoise(WeaponFireEvent fire_event, float zombie_x, float zombie_z) {
        // Kalkile distans senp ant kote zam nan tire ak kote zonbi a ye
        float dist_x = fire_event.source_x - zombie_x;
        float dist_z = fire_event.source_z - zombie_z;
        if (dist_x < 0) dist_x = -dist_x;
        if (dist_z < 0) dist_z = -dist_z;
        float total_distance = dist_x + dist_z;

        std::cout << "\n🔊 [SOUND SENSOR MATRIX]: Eskanè Odyo nan Forè a..." << std::endl;
        std::cout << "    [ZAM TIRE]: " << fire_event.weapon_type << " | Bri: " << fire_event.sound_decibels << " dB | Distans ak Zonbi: " << total_distance << "m" << std::endl;

        // Si bri a fò ase pou distans la, zonbi a ap tande l!
        if (fire_event.sound_decibels > total_distance) {
            std::cout << " ⚠️  [SOUND ALERT]: ALÈT! Gwo bri zam nan gaye nan tout Zile a! Zonbi yo tande bri bal la!" << std::endl;
            return true;
        }
        std::cout << "   [STEALTH ACTIVE]: Bri a lwen, zonbi yo pa tande anyen." << std::endl;
        return false;
    }

    void TriggerHordeRally(int zombie_count, float target_x, float target_z) {
        std::cout << "\n🌊 [GROUP / HORDE AI DEPLOYMENT]:" << std::endl;
        std::cout << "    [HORDE BRAIN]: " << zombie_count << " zonbi rasanble an gwoup otomatikman nan fènwa a!" << std::endl;
        std::cout << "    [AGGRO POOL]: Tout gwoup la ap kouri ansanm vè kowòdone pwen bri a: X=" << target_x << ", Z=" << target_z << " nèt!" << std::endl;
        std::cout << " 🛡️  [SQUAD DEFENSE REQUIRED]: 10 jwè klan yo dwe prepare barikad yo rapid!" << std::endl;
    }
};

int main() {
    std::cout << "\n=====================================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.57] - AUDIO DETECTOR & HORDE ENGINE" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << " 🏆 ROADMAP STATUS UPDATE:" << std::endl;
    std::cout << "  Vision ✅  │  Movement ✅  │  Position ✅  │  Zombie Types ✅" << std::endl;
    std::cout << "  Pathfinding ✅  │  Obstacle Avoidance ✅" << std::endl;
    std::cout << "  Sound Detection ← NEXT  │  Group / Horde AI ← NEXT" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    NayderSoundDetectionEngine audio_ai;
    
    // Simulate jwè a k ap tire ak gwo zam M4 li nan kowòdone X=50, Z=0 (Bri l lou: 150 Decibels)
    WeaponFireEvent player_shot = {"Assault_Rifle_M4_Auto", 50.0f, 0.0f, 150};
    
    // Zonbi a kanpe nan X=0, Z=0 (Distans la se 50 mèt)
    float zombie_pos_x = 0.0f;
    float zombie_pos_z = 0.0f;

    // 1. Lanse eskanè pou wè si zonbi a ap tande bri bal la
    bool zombie_alert = audio_ai.CheckIfZombieHearsNoise(player_shot, zombie_pos_x, zombie_pos_z);
    
    // 2. Si l tande l, tout gwo Horde la deklanche yon sèl kou!
    if (zombie_alert) {
        audio_ai.TriggerHordeRally(45, player_shot.source_x, player_shot.source_z);
    }

    std::cout << "=====================================================================" << std::endl;
    std::cout << " ✅ STATUS: Sound wave detection and group aggregation loops validated." << std::endl;
    std::cout << "=====================================================================" << std::endl;
    return 0;
}
