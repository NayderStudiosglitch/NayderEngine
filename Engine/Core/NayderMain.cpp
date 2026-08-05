#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "Input.cpp"
#include "GameLoop.cpp"
#include <iostream>
#include <vector>
#include <cmath>

// 📐 FÒMÈT MATRÈS PWOJEKSYON LEGACY KI REYÈL SOU COMPATIBILITY MODE
void SetupPerspectiveProjection(float fov, float aspect, float near_z, float far_z) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float top = near_z * std::tan(fov * 0.5f * 3.14159265f / 180.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    glFrustum(left, right, bottom, top, near_z, far_z);
}

// 🎥 APLiKE KONTWÒL VIEW KAMERA SOU MATRIS MODELVIEW LA
void ApplyFPSCameraView(float x, float y, float z, float yaw, float pitch) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(yaw + 90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-x, -y, -z);
}

// 🟩 FONKSYON POU DESiNE GWO TERRAIN AN POLIGÒN DIRÈK (Bypassing strict VBO blocks)
void Desine_Real_Terrain_Grid() {
    glBegin(GL_LINES); // N ap fè yon bèl kadrijaj 3D neon pou n asire vizibilite a 100%
    glColor3f(0.0f, 1.0f, 0.4f); // Neon Green Terrain Lines
    float extent = 30.0f;
    float step = 1.5f;
    for (float i = -extent; i <= extent; i += step) {
        // Liy ki kouri sou aks X
        glVertex3f(-extent, -1.0f, i);
        glVertex3f(extent, -1.0f, i);
        // Liy ki kouri sou aks Z
        glVertex3f(i, -1.0f, -extent);
        glVertex3f(i, -1.0f, extent);
    }
    glEnd();
}

// 🧟 FONKSYON POU DESINE MODÈL ZOMBIE A (Gwo kib wouj 3D pèspektiv)
void Desine_Zombie_3D_Cube() {
    glBegin(GL_QUADS);
    // Face devan (Wouj klere)
    glColor3f(1.0f, 0.1f, 0.1f);
    glVertex3f(-0.5f, 0.0f,  0.5f); glVertex3f( 0.5f, 0.0f,  0.5f);
    glVertex3f( 0.5f, 2.0f,  0.5f); glVertex3f(-0.5f, 2.0f,  0.5f);
    // Face dèyè (Wouj fènwa)
    glColor3f(0.6f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, -0.5f); glVertex3f( 0.5f, 0.0f, -0.5f);
    glVertex3f( 0.5f, 2.0f, -0.5f); glVertex3f(-0.5f, 2.0f, -0.5f);
    // Gen lòt kote nou ka optimize pita, de (2) bwat sa yo sifi pou tès la
    glEnd();
}

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "  👑 [NAYDER ENGINE v0.3.1] - NATIVE COMPATIBILITY MODE" << std::endl;
    std::cout << "=======================================================" << std::endl;

    NayderOpenGLRenderer engine_runtime;
    NayderInputSystem input_engine;
    NayderGameLoopClock engine_clock(107.0);

    // Nou overwrite Renderer a pou l louvri fenèt la an Compatibility Profile!
    // Pou sa fèt rapid san chanje anpil fichye, nou ka fòse drapo a isit la
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // OpenGL 2.1 pou asire Compatibility fèm 100% sou Chromebook
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    GLFWwindow* active_window = glfwCreateWindow(1366, 768, "Neon Fall 17 - First Real 3D World View v0.3.1", nullptr, nullptr);
    if (!active_window) {
        std::cerr << "🚫 [ERROR]: Window failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(active_window);
    glfwSwapInterval(1);

    input_engine.ConfigureInputCallbacks(active_window);
    
    // Asire nou sourit la vizib pou tès la pa kwense kamera w
    glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // Konfigire pipeline grafik debaz la
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 1366, 768);

    // Pozisyon Kamera a (Kanpe nan mitan sèn nan, gade anba vè objè yo)
    float cam_x = 0.0f, cam_y = 3.0f, cam_z = 10.0f;
    float yaw = -90.0f, pitch = -15.0f;

    std::cout << "\n🚀 [COMPATIBILITY INTERFACE ACTIVE]: Launching real 3D geometry pipeline loop..." << std::endl;

    while (!glfwWindowShouldClose(active_window)) {
        engine_clock.TickClockStart();
        float dt = engine_clock.GetDeltaTime();

        // Klavye WASD pou n ka deplase andedan sèn nan pou tès la
        float move_speed = 5.0f * dt;
        if (glfwGetKey(active_window, GLFW_KEY_W) == GLFW_PRESS) cam_z -= move_speed;
        if (glfwGetKey(active_window, GLFW_KEY_S) == GLFW_PRESS) cam_z += move_speed;
        if (glfwGetKey(active_window, GLFW_KEY_A) == GLFW_PRESS) cam_x -= move_speed;
        if (glfwGetKey(active_window, GLFW_KEY_D) == GLFW_PRESS) cam_x += move_speed;

        // Pentire background la an bèl koulè Syèl Ble Klere
        glClearColor(0.4f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. CHAJÈ REAL PROJECTION PROFiLE
        SetupPerspectiveProjection(45.0f, 1366.0f / 768.0f, 0.1f, 150.0f);

        // 2. CHAJÈ REAL VIEW CAMERA PROFILE
        ApplyFPSCameraView(cam_x, cam_y, cam_z, yaw, pitch);

        // 3. RENDER THE REAL 3D GRID TERRAIN (v0.3.1 Ground Surface)
        Desine_Real_Terrain_Grid();

        // 4. RENDER MULTIPLE ZOMBIE ENTITIES (3D Shapes pass)
        // Zonbi 1 (Mitan sèn nan)
        glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);
        Desine_Zombie_3D_Cube();
        glPopMatrix();

        // Zonbi 2 (Bò dwat an background)
        glPushMatrix();
        glTranslatef(4.0f, -1.0f, -4.0f);
        Desine_Zombie_3D_Cube();
        glPopMatrix();

        glfwSwapBuffers(active_window);
        engine_clock.SynchronizeFrameRateLock();
        glfwPollEvents();
    }

    glfwDestroyWindow(active_window);
    glfwTerminate();
    return 0;
}
