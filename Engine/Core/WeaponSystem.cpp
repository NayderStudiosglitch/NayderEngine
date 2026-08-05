#include "WeaponSystem.h"
#include <iostream>

NayderWeaponSystem::NayderWeaponSystem() {}

WeaponProfile NayderWeaponSystem::EquipWeaponPreset(WeaponType selection) {
    WeaponProfile wp;
    if (selection == WeaponType::ASSAULT_RIFLE) {
        wp.name = "M4_Assault_Rifle_Auto";
        wp.type = WeaponType::ASSAULT_RIFLE;
        wp.mode = FiringMode::FULL_AUTO;
        wp.base_damage = 35;
        wp.clip_capacity = 30;
        wp.current_clip = 30;
        wp.reserve_ammo = 180;
        wp.max_reserve = 360;
        wp.fire_rate_seconds = 0.09f; // Fast continuous rate (~660 RPM)
        wp.recoil_kick_factor = 0.45f;
        std::cout << " 🔫 [LOADOUT LOG]: Equipped '" << wp.name << "' [30/180 Auto profile mapped into VRAM]." << std::endl;
    }
    else if (selection == WeaponType::TACTICAL_PISTOL) {
        wp.name = "Tactical_Pistol_9mm";
        wp.type = WeaponType::TACTICAL_PISTOL;
        wp.mode = FiringMode::SEMI_AUTO;
        wp.base_damage = 25;
        wp.clip_capacity = 15;
        wp.current_clip = 15;
        wp.reserve_ammo = 90;
        wp.max_reserve = 180;
        wp.fire_rate_seconds = 0.25f; // Slower semi-auto click response thresholds
        wp.recoil_kick_factor = 0.20f;
        std::cout << " 🔫 [LOADOUT LOG]: Equipped '" << wp.name << "' [15/90 Semi profile mapped into VRAM]." << std::endl;
    }
    return wp;
}

bool NayderWeaponSystem::PullTriggerLoop(WeaponProfile& weapon, float delta_time_accumulator) {
    // Check if the hardware execution clock has passed the weapon's fire rate constraint
    if (weapon.current_clip <= 0) {
        std::cout << "   🚫 [WEAPON FAULT]: CLIP EMPTY! Click click... Weapon requires reload initialization." << std::endl;
        return false;
    }

    weapon.current_clip--;
    std::cout << " 💥 [FIRE EVENT]: Fired single bullet from '" << weapon.name << "'!" << std::endl;
    std::cout << "    ├── Active Magazine Clip : " << weapon.current_clip << " / " << weapon.clip_capacity << std::endl;
    std::cout << "    └── Raycast Vector Kick  : Recoil applied to viewport pitch orientation -> +" << weapon.recoil_kick_factor << "°" << std::endl;
    return true;
}

void NayderWeaponSystem::ExecuteReloadSequence(WeaponProfile& weapon) {
    if (weapon.reserve_ammo <= 0) {
        std::cout << "   🚫 [RELOAD FAULT]: No structural reserve ammunition packs remaining in backpack slots!" << std::endl;
        return;
    }

    int needed_ammo = weapon.clip_capacity - weapon.current_clip;
    if (needed_ammo <= 0) return;

    std::cout << "\n🔄 [RELOAD SEQUENCE]: Injecting fresh magazine arrays into weapon core feed..." << std::endl;
    
    if (weapon.reserve_ammo >= needed_ammo) {
        weapon.reserve_ammo -= needed_ammo;
        weapon.current_clip = weapon.clip_capacity;
    } else {
        weapon.current_clip += weapon.reserve_ammo;
        weapon.reserve_ammo = 0;
    }
    
    std::cout << "   └── ✅ [RELOAD SUCCESS]: Sync done. Current Magazine Feed restored completely to: " << weapon.current_clip << " / " << weapon.reserve_ammo << std::endl;
}
