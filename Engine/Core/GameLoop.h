#pragma once
#include <chrono>
class NayderGameLoopClock {
private:
    std::chrono::high_resolution_clock::time_point last_time;
    double target_frame_time;
    float delta_time;
    float fps_counter;
    float fps_timer;
    int current_fps;
public:
    NayderGameLoopClock(double target_fps);
    void TickClockStart();
    void SynchronizeFrameRateLock();
    float GetDeltaTime() const;
    int GetCurrentFPS() const;
};
