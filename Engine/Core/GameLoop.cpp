#include "GameLoop.h"
#include <thread>
NayderGameLoopClock::NayderGameLoopClock(double target_fps) {
    target_frame_time = 1.0 / target_fps;
    last_time = std::chrono::high_resolution_clock::now();
    delta_time = 0.0f; fps_counter = 0.0f; fps_timer = 0.0f; current_fps = 0;
}
void NayderGameLoopClock::TickClockStart() {
    auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = current_time - last_time;
    last_time = current_time;
    delta_time = static_cast<float>(elapsed.count());
    fps_counter++; fps_timer += delta_time;
    if (fps_timer >= 1.0f) { current_fps = static_cast<int>(fps_counter); fps_counter = 0.0f; fps_timer = 0.0f; }
}
void NayderGameLoopClock::SynchronizeFrameRateLock() {
    auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> process_time = current_time - last_time;
    if (process_time.count() < target_frame_time) {
        double sleep_duration = target_frame_time - process_time.count();
        std::this_thread::sleep_for(std::chrono::duration<double>(sleep_duration));
    }
}
float NayderGameLoopClock::GetDeltaTime() const { return delta_time; }
int NayderGameLoopClock::GetCurrentFPS() const { return current_fps; }
