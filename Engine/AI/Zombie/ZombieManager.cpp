#include "ZombieManager.h"

#include <algorithm>
#include <iostream>

ZombieManager::ZombieManager()
{
}

void ZombieManager::SpawnZombie(const std::string& name)
{
    m_Zombies.push_back(std::make_unique<Zombie>(name));

    std::cout
        << "[ZombieManager] Spawned "
        << name
        << std::endl;
}

void ZombieManager::Update(float deltaTime)
{
    for (auto& zombie : m_Zombies)
    {
        zombie->Update(deltaTime);
    }
}

void ZombieManager::RemoveDeadZombies()
{
    m_Zombies.erase(

        std::remove_if(

            m_Zombies.begin(),

            m_Zombies.end(),

            [](const std::unique_ptr<Zombie>& zombie)
            {
                return zombie->IsDead();
            }),

        m_Zombies.end());
}

std::size_t ZombieManager::GetZombieCount() const
{
    return m_Zombies.size();
}
