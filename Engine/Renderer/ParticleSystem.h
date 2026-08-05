#pragma once
#include <string>
#include <vector>

enum class VFXType { EXPLOSION, FIRE, SMOKE, SNOW, RAIN, SPARKS, BLOOD_IMPACT, BULLET_IMPACT, FOG, NUKE_DUST };

struct ParticleNode {
    float pos_x, pos_y, pos_z;
    float vel_x, vel_y, vel_z;
    float life_span;
    float max_life;
    float alpha; // Color opacity fade coefficient
};

class NayderParticleSystem {
private:
    std::vector<ParticleNode> active_particles;
    int particle_pool_cap = 5000; // 5K Particle limit lock on the GPU

public:
    NayderParticleSystem();
    void SpawnVFXEmitter(VFXType type, float x, float y, float z, int count);
    void UpdateParticleLifeCycles(float delta_time);
    void RenderParticleBuffers();
};
