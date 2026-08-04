#include "Zombie.h"

#include <iostream>

Zombie::Zombie(const std::string& name)
{
    m_Name = name;

    m_State = ZombieState::IDLE;

    m_Health = 100.0f;
    m_Speed = 2.5f;
    m_Damage = 15.0f;

    m_VisionRange = 40.0f;
    m_HearingRange = 80.0f;

    m_PosX = 0.0f;
    m_PosY = 0.0f;
    m_PosZ = 0.0f;
}

void Zombie::Update(float deltaTime)
{
    switch (m_State)
    {
        case ZombieState::IDLE:
            std::cout << m_Name << " is idle.\n";
            break;

        case ZombieState::PATROL:
            std::cout << m_Name << " is patrolling.\n";
            break;

        case ZombieState::SEARCH:
            std::cout << m_Name << " is searching.\n";
            break;

        case ZombieState::CHASE:
            std::cout << m_Name << " is chasing the target.\n";
            break;

        case ZombieState::ATTACK:
            Attack();
            break;

        case ZombieState::DEAD:
            break;
    }
}

void Zombie::SetState(ZombieState state)
{
    m_State = state;
}

void Zombie::SetPosition(float x, float y, float z)
{
    m_PosX = x;
    m_PosY = y;
    m_PosZ = z;
}

bool Zombie::CanSeePlayer(
    float playerX,
    float playerY,
    float playerZ)
{
    float dx = playerX - m_PosX;
    float dy = playerY - m_PosY;
    float dz = playerZ - m_PosZ;

    float distanceSquared =
        dx * dx +
        dy * dy +
        dz * dz;

    if (distanceSquared <= m_VisionRange * m_VisionRange)
    {
        m_State = ZombieState::CHASE;

        std::cout << m_Name
                  << " spotted the player.\n";

        return true;
    }

    m_State = ZombieState::PATROL;

    return false;
}

void Zombie::HearSound(float distance)
{
    if (distance <= m_HearingRange)
    {
        m_State = ZombieState::SEARCH;

        std::cout << m_Name
                  << " heard a sound.\n";
    }
}

void Zombie::SeeTarget(bool playerVisible)
{
    if (playerVisible)
    {
        m_State = ZombieState::CHASE;

        std::cout << m_Name
                  << " spotted the player.\n";
    }
}

void Zombie::Attack()
{
    std::cout << m_Name
              << " attacks for "
              << m_Damage
              << " damage.\n";
}

void Zombie::Die()
{
    m_State = ZombieState::DEAD;

    std::cout << m_Name
              << " died.\n";
}

bool Zombie::IsDead() const
{
    return m_State == ZombieState::DEAD;
}

