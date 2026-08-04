#include <iostream>
#include <string>

enum class HitboxZone { Head, Body, Leg };
struct ZombieBlackboard { std::string zombie_id = "Zombie_Runner_01"; int hp = 100; float current_speed = 5.0f; };

class ZombieCombatModule {
public:
    void RegisterHitImpact(ZombieBlackboard& zombie, HitboxZone zone, int base_damage) {
        int final_damage = base_damage;
        std::string modifier_flag = "Normal";

        std::cout << "\n🎯 [DAMAGE ZONES]: Bullet impact registered on " << zombie.zombie_id << "..." << std::endl;

        if (zone == HitboxZone::Head) {
            final_damage *= 3;
            modifier_flag = "CRITICAL_HEADSHOT";
        } else if (zone == HitboxZone::Leg) {
            zombie.current_speed *= 0.4f;
            modifier_flag = "LEG_CRIPPLED_SLOW";
        }

        zombie.hp -= final_damage;
        std::cout << "   [GPU HITBOX LOG]: Damage: " << final_damage << " HP [" << modifier_flag << "]" << std::endl;
        std::cout << "   [STATS]: HP: " << zombie.hp << " | Speed: " << zombie.current_speed << " m/s" << std::endl;
    }
};
