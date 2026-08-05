#pragma once
#include <string>

enum class EngineSystemState { FRONTEND_MENU, RUNTIME_GAMEPLAY, SHUTDOWN_SEQUENCE };

class NayderMainMenuEngine {
public:
    NayderMainMenuEngine();
    void RenderFrontendCanvas(int active_fps);
    EngineSystemState EvaluateSelectionInput(char user_choice_token);
};
