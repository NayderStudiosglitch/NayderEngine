#include "Inventory.h"
#include <iostream>

NayderInventoryEngine::NayderInventoryEngine() {
    active_slot_index = 0;
    slots_pool.clear();
}

void NayderInventoryEngine::InitializeDefaultSlots(NayderWeaponSystem& weapon_core) {
    std::cout << "\n🎒 [INVENTORY CORE]: Initializing tactical pack matrix storage arrays..." << std::endl;
    
    // Allocate Primary Slot: ID 0 (M4 Rifle Auto Profile)
    InventorySlot primary_slot;
    primary_slot.slot_id = 0;
    primary_slot.is_occupied = true;
    primary_slot.weapon_data = weapon_core.EquipWeaponPreset(WeaponType::ASSAULT_RIFLE);
    slots_pool.push_back(primary_slot);

    // Allocate Secondary Slot: ID 1 (Tactical Pistol 9mm Profile)
    InventorySlot secondary_slot;
    secondary_slot.slot_id = 1;
    secondary_slot.is_occupied = true;
    secondary_slot.weapon_data = weapon_core.EquipWeaponPreset(WeaponType::TACTICAL_PISTOL);
    slots_pool.push_back(secondary_slot);

    std::cout << "   └── ✅ [PACK SECURED]: 2 Functional Weapon Slots mapped to hardware storage grids." << std::endl;
}

void NayderInventoryEngine::CycleActiveSlotSelection(int target_index) {
    if (target_index < 0 || target_index >= static_cast<int>(slots_pool.size())) return;
    
    if (target_index == active_slot_index) return; // Already selected

    active_slot_index = target_index;
    std::cout << "\n🔄 [HOT-SWAP EVENT]: Swapped active gear profile to Slot #" << active_slot_index << " -> \"" 
              << slots_pool[active_slot_index].weapon_data.name << "\" initialized in combat hand matrix!" << std::endl;
}

WeaponProfile& NayderInventoryEngine::GetActiveWeaponProfile() {
    return slots_pool[active_slot_index].weapon_data;
}

int NayderInventoryEngine::GetActiveSlotIndex() const {
    return active_slot_index;
}
