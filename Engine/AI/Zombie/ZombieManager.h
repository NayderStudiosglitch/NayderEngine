#pragma once

#include "Zombie.h"

#include <memory>
#include <vector>
#include <string>

class ZombieManager
{
public:

    ZombieManager();

    void SpawnZombie(const std::string& name);

    void Update(float deltaTime);

    void RemoveDeadZombies();

    std::size_t GetZombieCount() const;

private:

    std::vector<std::unique_ptr<Zombie>> m_Zombies;
};
