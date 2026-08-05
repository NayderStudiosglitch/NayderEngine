#pragma once
#include <string>
#include <vector>

struct BoneTransform {
    std::string bone_name;
    float position_xyz[3];
    float quaternion_rotation[4]; // Precise 3D rotation data
};

struct AnimationClip {
    std::string animation_name;
    int total_keyframes = 0;
    float duration_seconds = 0.0f;
};

class NayderAnimationEngine {
private:
    std::string active_animation_state;
    float current_time_track;

public:
    NayderAnimationEngine();
    void ConfigureSkeletalRig(std::string model_id, int bone_count);
    void RegisterAnimationClip(AnimationClip clip);
    void BlendAnimationStates(std::string from_state, std::string to_state, float blend_factor);
    void UpdateSkeletalShaderUniforms();
};
