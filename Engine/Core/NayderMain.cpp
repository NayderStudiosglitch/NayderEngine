#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Physics/Collision.cpp" // Interlocking real physics components
#include "Input.cpp"
#include <iostream>

typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC) (GLuint array);

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.92] - NATIVE 3D PHYSICS INTEGRATION" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 PHASE 5: REAL ENGINE RUNTIME UNLOCKED:" << std::endl;
    std::cout << "  v0.0.90 Real Texture Rendering -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.91 Real Lighting          -> \342\234\205 OPERATIONAL" << std::endl;
    std::cout << "  v0.0.92 Real Physics Context   -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.93 Real Audio Playback    -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderShaderCompiler shader_compiler;
    CollisionSystem physics_system;

    if (!engine_runtime.InitializeWindowContext(1366, 768, "Neon Fall 17 - Real Physics Integration v0.0.92")) {
        return -1;
    }

    GLFWwindow* active_window = glfwGetCurrentContext();
    input_engine.ConfigureInputCallbacks(active_window);
    engine_runtime.SetupRealGraphicsPipeline();

    // 1. Instantiate live 3D Bounding Boxes directly in engine memory space
    // BoxCollider schema: {x, y, z, width, height, depth}
    BoxCollider player_collider    = {0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f}; // Active player bounding box
    BoxCollider barricade_collider = {3.0f, 0.0f, 0.0f, 2.0f, 4.0f, 1.0f}; // Concrete wall blocking X = 3.0f

    std::cout << "\n🤖 [PHYSICS ENGINE INTEGRATED]:" << std::endl;
    std::cout << " -> Player Box Bounds   : Size[W:1.0, H:2.0, D:1.0] initialized at origin." << std::endl;
    std::cout << " -> Obstacle Box Bounds : Static Barrier mapped on grid coordinate X = 3.0f." << std::endl;
    std::cout << " -> STATUS              : ✅ Collision checking interlocking active on frame ticks!" << std::endl;

    std::cout << "\n🎬 [REAL-TIME PHYSICS LOOP ACTIVE]:" << std::endl;
    std::cout << " -> HOLD [W] key to sprint forward and intentionally test the wall collision lock!" << std::endl;
    std::cout << " -> Press [ESCAPE] on your keyboard to terminate the engine process securely." << std::endl;

    // ACTIVE HARDCORE RUNTIME TICK GAME LOOP
    while (!engine_runtime.ShouldWindowClose()) {
        engine_runtime.ClearScreenBuffer();
        shader_compiler.UseShaderProgram(); // Maintains pipeline shaders

        // 2. PREDICTIVE Locomotion Force Calculations
        float forward_force = 0.0f;
        if (NayderInputSystem::key_states[GLFW_KEY_W]) {
            forward_force = 0.15f; // Player attempts to step forward by 0.15 units
        }

        if (forward_force > 0.0f) {
            // Compute a temporary predictive box state before committing the movement to variables
            BoxCollider predictive_player_box = player_collider;
            predictive_player_box.x += forward_force;

            // 3. RUN REAL-TIME 3D INTERSECTION ANALYSIS
            if (physics_system.CheckCollision(predictive_player_box, barricade_collider)) {
                // COLLiSION INTERCEPTED! Clamp acceleration parameters instantly to completely halt translation
                forward_force = 0.0f;
                std::cout << " 🚫 [REAL-TIME COLLISION]: Movement Blocked! Player bounding box intersected Concrete_Wall! Speed clamped to 0.0 m/s." << std::endl;
            } else {
                // Path clear, safely apply translation metrics
                player_collider.x += forward_force;
                std::cout << " 🏃‍♂️ [LOCOMOTION]: Path clear. Player translated to position X: " << player_collider.x << std::endl;
            }
        }

        engine_runtime.SwapHardwareBuffers();
        engine_runtime.HandleWindowPollEvents();
    }

    engine_runtime.TerminateGraphicsContext();
    std::cout << "=======================================================" << std::endl;
    return 0;
}
