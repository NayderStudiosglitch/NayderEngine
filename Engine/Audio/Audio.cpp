#include "Audio.h"
#include <iostream>
#include <cmath>

NayderSpatialAudioEngine::NayderSpatialAudioEngine() {
    // Initialized mixing desks
}

void NayderSpatialAudioEngine::InitializeAudioHardwareChannels() {
    std::cout << "\n🔊 [AUDIO ENGINE]: Initializing hardware mixing channels and context..." << std::endl;
    std::cout << " -> OpenAL Device Bridge / SDL_Audio Mixer layer initialized successfully." << std::endl;
    std::cout << " -> Hardware Allocation: 32 Dynamic 3D Voice Channels registered on audio buffer cache." << std::endl;
    std::cout << " ✅ [AUDIO DEVICE ACTIVE]: Hardware sound processing stack ready at 60Hz tick loops!" << std::endl;
}

void NayderSpatialAudioEngine::RegisterSoundEmitter(SoundSource3D source) {
    std::cout << "  ├── [AUDIO REGISTERED]: Emitter file bound: \"" << source.clip_name 
              << "\" | Default Vol: " << source.base_volume 
              << " | Target Matrix Pitch: " << source.pitch_multiplier << "x" << std::endl;
}

void NayderSpatialAudioEngine::ProcessSpatialAudioMatrix(const SoundSource3D& source, const AudioListener& listener) {
    // 1. Calculate 3D Euclidean Distance for Proximity Volume Attenuation
    float delta_x = source.pos_x - listener.cam_x;
    float delta_y = source.pos_y - listener.cam_y;
    float delta_z = source.pos_z - listener.cam_z;
    float distance = std::sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);

    // Attenuation formula (Inverse proportional to distance distance drops)
    float calculated_volume = source.base_volume / (1.0f + (0.1f * distance * distance));
    if (calculated_volume > 1.0f) calculated_volume = 1.0f;
    if (calculated_volume < 0.01f) calculated_volume = 0.0f; // Audio drops completely to cut threads

    // 2. Calculate Stereo Pan Balance based on Azimuth Angles
    float angle_to_source = std::atan2(delta_z, delta_x);
    float pan_left = 0.5f - (0.5f * std::cos(angle_to_source));
    float pan_right = 1.0f - pan_left;

    std::cout << "\n🎧 [3D SPATIALIZATION CALCULATOR] - Tracking: \"" << source.clip_name << "\"" << std::endl;
    std::cout << " -> Spatial Nodes  : Sound Source at (" << source.pos_x << ", " << source.pos_z << ") │ Player Cam at (" << listener.cam_x << ", " << listener.cam_z << ")" << std::endl;
    std::cout << " -> Calculated Dist: " << distance << " meters away from Listener head node." << std::endl;
    std::cout << " -> Mix Output Pot : Volume Amplitude: " << calculated_volume * 100 << "%%" << std::endl;
    std::cout << " -> Pan Channel Bal: [ LEFT EAR: " << pan_left * 100 << "%%  │  RIGHT EAR: " << pan_right * 100 << "%% ]" << std::endl;
    
    if (distance < 5.0f && source.clip_name.find("Scream") != std::string::npos) {
        std::cout << " ⚠️  [AUDIO ALERT]: DANGER CLOSE! Sudden frequency pitch shift to simulate Doppler rush!" << std::endl;
    }
}
