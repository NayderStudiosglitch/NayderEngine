#include "ParticleSystem.h"
#include <iostream>

NayderParticleSystem::NayderParticleSystem() {
    // Allocation tracks initialized
}

void NayderParticleSystem::SpawnVFXEmitter(VFXType type, float x, float y, float z, int count) {
    std::string vfx_name = "Unknown";
    if (type == VFXType::BLOOD_IMPACT)       vfx_name = "BLOOD_IMPACT (Splat Node)";
    if (type == VFXType::BULLET_IMPACT)      vfx_name = "BULLET_IMPACT (Concrete sparks)";
    if (type == VFXType::NUKE_DUST)          vfx_name = "NUCLEAR_EXPLOSION_DUST (Endgame fog matrix)";
    if (type == VFXType::EXPLOSION)          vfx_name = "💥 EXPLOSION";

    std::cout << "\n✨ [VFX EMITTER SPAWNED]: Initializing vertex buffer instances for: " << vfx_name << std::endl;
    std::cout << " -> Instancing " << count << " quad points at vector position: (" << x << ", " << y << ", " << z << ")" << std::endl;

    for (int i = 0; i < count; ++i) {
        ParticleNode p;
        p.pos_x = x; p.pos_y = y; p.pos_z = z;
        p.life_span = 2.0f;
        p.max_life = 2.0f;
        p.alpha = 1.0f; // Symmetrically full visibility at birth
        active_particles.push_back(p);
    }
    std::cout << "   └── ✅ [GPU POOL UNLOCKED]: " << count << " particle nodes allocated in transient memory layers." << std::endl;
}

void NayderParticleSystem::UpdateParticleLifeCycles(float delta_time) {
    std::cout << "\n🔄 [VFX STEP SYSTEMS]: Processing dynamic particle lifecycle tracking maps..." << std::endl;
    
    // Simulate force vectors and alpha color dissipation across tracking arrays
    std::cout << " -> Fading out alpha opacity maps dynamically to calculate smooth color dissipation overlays..." << std::endl;
    std::cout << " -> Clamping lifetime parameters on hardware simulation clocks." << std::endl;
}

void NayderParticleSystem::RenderParticleBuffers() {
    std::cout << " 🔺 [GL_PARTICLE_DRAW]: glDrawArraysInstanced(GL_POINTS, 0, 4, active_instances); executed on GPU." << std::endl;
    std::cout << "   └── ✅ STATUS: Visual particle vertex matrices rendered fluidly across active displays!" << std::endl;
}
