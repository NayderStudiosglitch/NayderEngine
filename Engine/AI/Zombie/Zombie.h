#pragma once

#include <string>

enum class ZombieState
{
    IDLE,
    PATROL,
    SEARCH,
    CHASE,
    ATTACK,
    DEAD
};

class Zombie
{
public:

    Zombie(const std::string& name);

    void Update(float deltaTime);

    void SetState(ZombieState state);

    void SetPosition(float x, float y, float z);

    bool CanSeePlayer(
        float playerX,
        float playerY,
        float playerZ);

    void HearSound(float distance);

    void SeeTarget(bool playerVisible);

    void Attack();

    void Die();

    bool IsDead() const;

private:

    std::string m_Name;

    ZombieState m_State;

    float m_Health;
    float m_Speed;
    float m_Damage;

    float m_VisionRange;
    float m_HearingRange;

    float m_PosX;
    float m_PosY;
    float m_PosZ;
};
