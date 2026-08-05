#pragma once
#include "WeaponSystem.h"
#include <vector>

struct InventorySlot {
    int slot_id;
    bool is_occupied;
    WeaponProfile weapon_data;
};

class NayderInventoryEngine {
private:
    std::vector<InventorySlot> slots_pool;
    int active_slot_index;

public:
    NayderInventoryEngine();
    void InitializeDefaultSlots(NayderWeaponSystem& weapon_core);
    void CycleActiveSlotSelection(int target_index);
    WeaponProfile& GetActiveWeaponProfile();
    int GetActiveSlotIndex() const;
};
