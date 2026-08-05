#include <iostream>
#include <string>
#include <vector>
#include <cmath>

enum class LODLevel
{
    HIGH_POLY,
    MEDIUM_POLY,
    LOW_POLY
};

struct MeshComponent
{
    std::string mesh_name;
    int vertex_count;
    LODLevel active_lod;
};

struct Entity
{
    std::string name;
    float pos_x;
    float pos_y;
    float pos_z;

    bool is_in_camera_view;

    MeshComponent mesh;
};

class NayderNextGenRenderOptimizer
{
private:
    float field_of_view;
    float max_visible_distance;

public:

    NayderNextGenRenderOptimizer()
    {
        field_of_view = 90.0f;
        max_visible_distance = 500.0f;
    }

    void ExecuteFrustumCullingAndLOD(
        Entity& entity,
        float cam_x,
        float cam_y,
        float cam_z)
    {
        float distance =
            std::sqrt(
                std::pow(entity.pos_x - cam_x, 2) +
                std::pow(entity.pos_y - cam_y, 2) +
                std::pow(entity.pos_z - cam_z, 2));

        entity.is_in_camera_view =
            distance <= max_visible_distance;

        if (distance < 80.0f)
            entity.mesh.active_lod = LODLevel::HIGH_POLY;
        else if (distance < 200.0f)
            entity.mesh.active_lod = LODLevel::MEDIUM_POLY;
        else
            entity.mesh.active_lod = LODLevel::LOW_POLY;

        std::cout
            << "[ENTITY] "
            << entity.name
            << std::endl;

        std::cout
            << " Distance : "
            << distance
            << " m"
            << std::endl;

        std::cout
            << " Visible  : "
            << (entity.is_in_camera_view ? "YES" : "NO")
            << std::endl;

        std::cout
            << " LOD      : ";

        switch(entity.mesh.active_lod)
        {
            case LODLevel::HIGH_POLY:
                std::cout << "HIGH";
                break;

            case LODLevel::MEDIUM_POLY:
                std::cout << "MEDIUM";
                break;

            case LODLevel::LOW_POLY:
                std::cout << "LOW";
                break;
        }

        std::cout << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }

    void RunHardwareSimulation()
    {
        float camera_x = 0.0f;
        float camera_y = 0.0f;
        float camera_z = 0.0f;

        Entity building =
        {
            "Cyberpunk_Neon_Tower_01",
            0.0f,
            0.0f,
            25.0f,
            false,
            {"Mesh_Tower",15000,LODLevel::HIGH_POLY}
        };

        Entity zombie =
        {
            "Zombie_Boss_Alpha",
            0.0f,
            0.0f,
            350.0f,
            false,
            {"Mesh_Zombie",8000,LODLevel::HIGH_POLY}
        };

        Entity helicopter =
        {
            "Military_Chopper_05",
            0.0f,
            0.0f,
            -40.0f,
            false,
            {"Mesh_Chopper",12000,LODLevel::HIGH_POLY}
        };

        ExecuteFrustumCullingAndLOD(
            building,
            camera_x,
            camera_y,
            camera_z);

        ExecuteFrustumCullingAndLOD(
            zombie,
            camera_x,
            camera_y,
            camera_z);

        ExecuteFrustumCullingAndLOD(
            helicopter,
            camera_x,
            camera_y,
            camera_z);

        std::cout << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "NAYDER ENGINE v0.0.64" << std::endl;
        std::cout << "Frustum Culling : ONLINE" << std::endl;
        std::cout << "Dynamic LOD     : ONLINE" << std::endl;
        std::cout << "Renderer        : READY" << std::endl;
        std::cout << "==========================================" << std::endl;
    }
};

int main()
{
    NayderNextGenRenderOptimizer engine;

    engine.RunHardwareSimulation();

    return 0;
}

