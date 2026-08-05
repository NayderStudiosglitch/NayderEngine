#include "Audio.h"
#include <iostream>
#include <fstream>
#include <vector>
NayderAudioRuntime::NayderAudioRuntime() { pcm_handle = nullptr; }
bool NayderAudioRuntime::InitializeAudioHardware() {
    int rc = snd_pcm_open(&pcm_handle, device_name.c_str(), SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) {
        std::cerr << " 🚫 [ALSA AUDIO ERROR]: Initialization failed." << std::endl;
        return false;
    }
    rc = snd_pcm_set_params(pcm_handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 500000);
    if (rc < 0) {
        std::cerr << " 🚫 [ALSA CONFIG ERROR]: Parameter setup failed." << std::endl;
        return false;
    }
    std::cout << "\n🔊 [REAL AUDIO RUNTIME ACTIVE]: 44100Hz Stereo Channels Initialized Successfully!" << std::endl;
    return true;
}
void NayderAudioRuntime::PlayRealWavFile(const std::string& wav_path) {
    if (!pcm_handle) return;
    std::ifstream file(wav_path, std::ios::binary);
    if (!file) {
        std::cerr << " 🚫 [AUDIO STREAM ERROR]: Cannot open file: " << wav_path << std::endl;
        return;
    }
    file.seekg(44);
    std::vector<char> buffer(1024 * 16);
    std::cout << " 💥 [AUDIO HARDWARE TRIGGER]: Playing: " << wav_path << std::endl;
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        std::streamsize bytes_read = file.gcount();
        snd_pcm_sframes_t frames = snd_pcm_writei(pcm_handle, buffer.data(), bytes_read / 4);
        if (frames < 0) frames = snd_pcm_prepare(pcm_handle);
    }
    file.close();
}
void NayderAudioRuntime::TerminateAudioContext() {
    if (pcm_handle) { snd_pcm_drain(pcm_handle); snd_pcm_close(pcm_handle); }
}
