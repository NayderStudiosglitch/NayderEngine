#include <iostream>
#include <string>
#include <vector>

struct TransformComponent
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct HealthComponent
{
    int current_hp = 100;
    bool is_dead = false;
};

struct AIComponent
{
    std::string zombie_type = "Runner";
    float speed = 4.0f;
};

class Entity
{
public:
    std::string entity_id;
    std::string entity_tag;

    TransformComponent transform;
    HealthComponent health;
    AIComponent ai;

    Entity(std::string id, std::string tag)
    {
        entity_id = id;
        entity_tag = tag;
    }
};

class NayderWorldSceneGraph
{
private:
    std::vector<Entity> scene_entities;

public:
    void AddEntityToWorld(const Entity& entity)
    {
        scene_entities.push_back(entity);

        std::cout
            << "[WORLD] Added Entity: "
            << entity.entity_id
            << " ("
            << entity.entity_tag
            << ")"
            << std::endl;
    }

    void UpdateWorldMatrix()
    {
        std::cout
            << "\n[WORLD] Updating Scene Graph..."
            << std::endl;

        for (const auto& entity : scene_entities)
        {
            std::cout
                << "  -> "
                << entity.entity_id
                << " Position("
                << entity.transform.x << ", "
                << entity.transform.y << ", "
                << entity.transform.z << ")"
                << std::endl;
        }
    }
};

int main()
{
    std::cout
        << "=======================================================\n";
    std::cout
        << "   NAYDER ENGINE v0.0.61 - ENTITY SYSTEM\n";
    std::cout
        << "=======================================================\n";

    std::cout
        << "v0.0.61 Entity System          -> ONLINE\n";
    std::cout
        << "v0.0.62 World & Scene Interface-> ONLINE\n";
    std::cout
        << "v0.0.63 Collision System       -> NEXT\n";
    std::cout
        << "-------------------------------------------------------\n";

    NayderWorldSceneGraph world_scene;

    Entity player("NAYDER_01", "PLAYER_SQUAD");
    player.transform.x = 10.0f;

    Entity zombie1("Zombie_Alpha_01", "ZOMBIE_RUNNER");

    Entity zombie2("Zombie_Brute_02", "ZOMBIE_BRUTE");
    zombie2.health.current_hp = 250;

    world_scene.AddEntityToWorld(player);
    world_scene.AddEntityToWorld(zombie1);
    world_scene.AddEntityToWorld(zombie2);

    world_scene.UpdateWorldMatrix();

    std::cout
        << "=======================================================\n";

    return 0;
}

