#pragma once
#include <string>
#include <vector>
#include <alsa/asoundlib.h>

class NayderAudioRuntime {
private:
    snd_pcm_t* pcm_handle;
    std::string device_name = "default";

public:
    NayderAudioRuntime();
    bool InitializeAudioHardware();
    void PlayRealWavFile(const std::string& wav_path);
    void TerminateAudioContext();
};
