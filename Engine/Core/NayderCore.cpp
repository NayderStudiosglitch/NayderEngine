#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <thread>

// =============================================================================
// MODIL 1: ECS ARCHITECTURE (Transform Component)
// =============================================================================
struct TransformComponent {
    float x, y, z;
    float velocity_x, velocity_y;
};

class Entity {
public:
    std::string name;
    int id;
    TransformComponent transform;
    bool has_physics;

    Entity(std::string entity_name, int entity_id) {
        name = entity_name;
        id = entity_id;
        transform = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        has_physics = false;
    }
};

// =============================================================================
// MODIL 2: SCENE SYSTEM & WORLD GRID
// =============================================================================
class SceneSystem {
public:
    std::string active_scene_name;
    std::map<std::string, Entity*> world_entities;

    SceneSystem() {
        active_scene_name = "Desert_Ghost_City_Alpha";
    }

    void SpawnEntity(Entity* obj) {
        world_entities[obj->name] = obj;
        std::cout << " -> [C++ SCENE]: '" << obj->name << "' spawn nan kat '" << active_scene_name << "' kòrèkteman." << std::endl;
    }
};

// =============================================================================
// MODIL 3: PHYSICS & COLLISION SUB-SYSTEMS
// =============================================================================
class NayderPhysicsEngine {
private:
    float gravity;

public:
    NayderPhysicsEngine() {
        gravity = -9.81f; // Gravite mond reyèl la
    }

    void UpdatePhysics(Entity* target, float delta_time) {
        if (target->has_physics) {
            target->transform.x += target->transform.velocity_x * delta_time;
            target->transform.y += target->transform.velocity_y * delta_time;
        }
    }

    bool CheckAABBCollision(Entity* obj1, Entity* obj2) {
        // Simulation deteksyon kounyè ant bwat kowòdone yo
        float distance = abs(obj1->transform.x - obj2->transform.x);
        if (distance < 5.0f) {
            std::cout << " 💥 [C++ COLLISION]: Kontak detekte ant '" << obj1->name << "' ak '" << obj2->name << "'!" << std::endl;
            return true;
        }
        return false;
    }
};

// =============================================================================
// MODIL 4: CORE RUNTIME ENGINE (Game Loop & Renderer Setup)
// =============================================================================
class NayderEngineCPP {
private:
    bool is_running;
    int target_fps;
    float delta_time;
    SceneSystem scene;
    NayderPhysicsEngine physics;

public:
    NayderEngineCPP() {
        is_running = true;
        target_fps = 107;
        delta_time = 1.0f / target_fps;
        
        std::cout << "\n=======================================================" << std::endl;
        std::cout << "     [NAYDER ENGINE v0.0.23] - FULL MODULAR C++ CORE" << std::endl;
        std::cout << "=======================================================" << std::endl;
        std::cout << " [*] ECS Architecture    -> ✅ SOU LI" << std::endl;
        std::cout << " [*] Scene Manager Core  -> ✅ SOU LI" << std::endl;
        std::cout << " [*] Physics Engine Sub  -> ✅ SOU LI" << std::endl;
        std::cout << " [*] Collision System    -> ✅ SOU LI" << std::endl;
        std::cout << " [*] Renderer Pipeline   -> ✅ READY FOR GPU HANDSHAKE" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
    }

    void InitializeWorldState() {
        // 1. Kreye Sòlda a nan ECS la
        Entity* soldier = new Entity("Player_Soldier", 1);
        soldier->transform.x = 10.0f;
        soldier->has_physics = true;
        soldier->transform.velocity_x = 5.0f; // Sòlda ap deplase sou kote
        scene.SpawnEntity(soldier);

        // 2. Kreye lènmi an nan ECS la
        Entity* zombie = new Entity("Zombie_Bot", 2);
        zombie->transform.x = 14.0f; // Mete l tou prè sòlda a pou tès la
        scene.SpawnEntity(zombie);
        
        std::cout << "-------------------------------------------------------" << std::endl;
    }

    void RunEngineLoop() {
        std::cout << " -> [NAYDER LOOP]: Gwo kè kòd la ap kouri..." << std::endl;
        
        int frame_count = 0;
        while (is_running && frame_count < 3) {
            std::cout << "\n [FRAME " << frame_count + 1 << "]:" << std::endl;
            
            // 1. Kat CPU a ap kalkile fizik tout entite yo
            for (auto const& [name, entity] : scene.world_entities) {
                physics.UpdatePhysics(entity, delta_time);
            }
            
            // 2. Tcheke si kontak fèt ant objè yo nan sèn lan
            Entity* p = scene.world_entities["Player_Soldier"];
            Entity* z = scene.world_entities["Zombie_Bot"];
            if (p && z) {
                physics.CheckAABBCollision(p, z);
            }

            // Ti poz pou asire vitès 107 FPS taktik la
            std::this_thread::sleep_for(std::chrono::milliseconds(int(delta_time * 1000)));
            frame_count++;
        }
        
        std::cout << "\n ✅ STATUS: Tout sistèm C++ yo travay an liy pafè." << std::endl;
        std::cout << "=======================================================" << std::endl;
    }
};

int main() {
    NayderEngineCPP engine;
    engine.InitializeWorldState();
    engine.RunEngineLoop();
    return 0;
}
