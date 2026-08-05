#pragma once
#include <string>
#include <vector>

struct SoundSource3D {
    std::string clip_name;
    float pos_x;
    float pos_y;
    float pos_z;
    float base_volume = 1.0f;
    float pitch_multiplier = 1.0f;
};

struct AudioListener {
    float cam_x;
    float cam_y;
    float cam_z;
    float look_x;
    float look_z;
};

class NayderSpatialAudioEngine {
public:
    NayderSpatialAudioEngine();
    void InitializeAudioHardwareChannels();
    void RegisterSoundEmitter(SoundSource3D source);
    void ProcessSpatialAudioMatrix(const SoundSource3D& source, const AudioListener& listener);
};
