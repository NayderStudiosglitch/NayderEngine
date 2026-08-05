#pragma once
#include <string>

enum class WeaponType { ASSAULT_RIFLE, TACTICAL_PISTOL, PUMP_SHOTGUN };
enum class FiringMode { FULL_AUTO, SEMI_AUTO, PUMP_ACTION };

struct WeaponProfile {
    std::string name;
    WeaponType type;
    FiringMode mode;
    int base_damage;
    int clip_capacity;
    int current_clip;
    int reserve_ammo;
    int max_reserve;
    float fire_rate_seconds; // Time gap constraint between individual shots
    float recoil_kick_factor;
};

class NayderWeaponSystem {
public:
    NayderWeaponSystem();
    WeaponProfile EquipWeaponPreset(WeaponType selection);
    bool PullTriggerLoop(WeaponProfile& weapon, float delta_time_accumulator);
    void ExecuteReloadSequence(WeaponProfile& weapon);
};
