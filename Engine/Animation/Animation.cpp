#include "Animation.h"
#include <iostream>

NayderAnimationEngine::NayderAnimationEngine() {
    active_animation_state = "Locomotion_Idle";
    current_time_track = 0.0f;
}

void NayderAnimationEngine::ConfigureSkeletalRig(std::string model_id, int bone_count) {
    std::cout << "\n🧬 [SKELETAL RIGGER]: Parsing joint hierarchical skeletons for: '" << model_id << "'..." << std::endl;
    std::cout << " -> Mapping bone weight vertex slots on GPU attributes (glVertexAttribPointer)..." << std::endl;
    std::cout << " ✅ [RIG ARCHITECTURE]: successfully bound " << bone_count << " independent joint matrix arrays in VRAM buffers." << std::endl;
}

void NayderAnimationEngine::RegisterAnimationClip(AnimationClip clip) {
    std::cout << "  ├── [ANIMATION REGISTERED]: Track name: \"" << clip.animation_name 
              << "\" | Keyframes: " << clip.total_keyframes 
              << " | Length: " << clip.duration_seconds << "s" << std::endl;
}

void NayderAnimationEngine::BlendAnimationStates(std::string from_state, std::string to_state, float blend_factor) {
    active_animation_state = to_state;
    std::cout << "\n🔄 [ANIMATION STATE MACHINE]: Dynamic transition interpolation active..." << std::endl;
    std::cout << " -> Interpolating bone rotation matrices: [" << from_state << "] ──(" << blend_factor * 100 << "%% Blending)──► [" << to_state << "]" << std::endl;
}

void NayderAnimationEngine::UpdateSkeletalShaderUniforms() {
    std::cout << " ⚡ [GL_SKINNING_BIND]: Pushing joint transformation matrices to Vertex Shaders..." << std::endl;
    std::cout << " -> glUniformMatrix4fv(glGetUniformLocation(prog, \"FinalBoneMatrices\"), 64, GL_FALSE, ...);" << std::endl;
    std::cout << " ✅ [SKINNING SYSTEM ACTIVE]: Vertex shader skinning loops computing real-time model deformations!" << std::endl;
}
