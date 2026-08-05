#pragma once
#include <string>

struct EntityHealthPool {
    std::string tag;
    int max_hp;
    int current_hp;
    int max_armor;
    int current_armor;
    bool is_dead;
};

class NayderHealthSystem {
public:
    NayderHealthSystem();
    void ApplyDamageToPlayer(EntityHealthPool& player, int raw_damage);
    bool ApplyDamageToZombie(int zombie_index, int& zombie_hp, bool& zombie_dead, int raw_damage);
};
