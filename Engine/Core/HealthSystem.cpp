#include "HealthSystem.h"
#include <iostream>

NayderHealthSystem::NayderHealthSystem() {}

void NayderHealthSystem::ApplyDamageToPlayer(EntityHealthPool& player, int raw_damage) {
    if (player.is_dead) return;

    std::cout << "\n🩸 [HEALTH SYSTEM]: Player taking incoming hit from zombie! Raw Damage: " << raw_damage << std::endl;

    // Armor absorb logic: 60% of damage goes to Armor if available
    if (player.current_armor > 0) {
        int armor_absorb = static_cast<int>(raw_damage * 0.6f);
        if (player.current_armor >= armor_absorb) {
            player.current_armor -= armor_absorb;
            player.current_hp -= (raw_damage - armor_absorb);
        } else {
            int leftover = raw_damage - player.current_armor;
            player.current_armor = 0;
            player.current_hp -= leftover;
        }
    } else {
        player.current_hp -= raw_damage;
    }

    if (player.current_hp <= 0) {
        player.current_hp = 0;
        player.is_dead = true;
        std::cout << " 🚨 [PLAYER ELIMINATED]: Hardcore Squad Host NAYDER_01 fell in combat! Mission failed!" << std::endl;
    } else {
        std::cout << "   └── [VITAL STATS]: Remaining HP: " << player.current_hp << " / " << player.max_hp << " │ Armor: " << player.current_armor << " AR" << std::endl;
    }
}

bool NayderHealthSystem::ApplyDamageToZombie(int zombie_index, int& zombie_hp, bool& zombie_dead, int raw_damage) {
    if (zombie_dead) return false;

    std::cout << "\n🎯 [COMBAT HIT]: Bullet raycast registered on Zombie_0" << zombie_index << "! Damage applied: " << raw_damage << " HP" << std::endl;
    zombie_hp -= raw_damage;

    if (zombie_hp <= 0) {
        zombie_hp = 0;
        zombie_dead = true;
        std::cout << "  💀 [ZOMBIE DESTROYED]: Zombie_0" << zombie_index << " dropped! Clearing physics bounds." << std::endl;
        return true; // Returns true to flag an active kill count increment
    } else {
        std::cout << "   └── [ZOMBIE STATS]: Target Zombie_0" << zombie_index << " HP dropped to: " << zombie_hp << "/100" << std::endl;
        return false;
    }
}
