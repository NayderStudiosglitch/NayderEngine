#include "../Renderer/Renderer.cpp"
#include "../Renderer/Shader.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Audio/Audio.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <GLFW/glfw3.h>
void SetupPerspectiveProjection(float fov, float aspect, float near_z, float far_z) {
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    float top = near_z * std::tan(fov * 0.5f * 3.14159265f / 180.0f);
    float bottom = -top; float right = top * aspect; float left = -right;
    glFrustum(left, right, bottom, top, near_z, far_z);
}
void ApplyFPSCameraView(float x, float y, float z, float yaw, float pitch) {
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glRotatef(pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(yaw + 90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-x, -y, -z);
}
void DrawRealistic3DHeightmapTerrain() {
    float extent = 45.0f; float step = 1.2f;
    float sun_x = 0.8f, sun_y = 0.3f, sun_z = -0.4f;
    float length = std::sqrt(sun_x*sun_x + sun_y*sun_y + sun_z*sun_z);
    sun_x /= length; sun_y /= length; sun_z /= length;
    glBegin(GL_TRIANGLES);
    for (float z = -extent; z < extent; z += step) {
        for (float x = -extent; x < extent; x += step) {
            float x0 = x, z0 = z; float x1 = x + step, z1 = z;
            float x2 = x, z2 = z + step; float x3 = x + step, z3 = z + step;
            float dist = std::sqrt(x0*x0 + z0*z0);
            float y0 = -1.2f; float y1 = -1.2f; float y2 = -1.2f; float y3 = -1.2f;
            if (dist > 7.0f) {
                y0 = (std::sin(x0 * 0.22f) * std::cos(z0 * 0.22f) * 3.8f) - 0.5f;
                y1 = (std::sin(x1 * 0.22f) * std::cos(z0 * 0.22f) * 3.8f) - 0.5f;
                y2 = (std::sin(x0 * 0.22f) * std::cos(z2 * 0.22f) * 3.8f) - 0.5f;
                y3 = (std::sin(x1 * 0.22f) * std::cos(z3 * 0.22f) * 3.8f) - 0.5f;
            }
            float v1_x = x1 - x0, v1_y = y1 - y0, v1_z = z1 - z0;
            float v2_x = x2 - x0, v2_y = y2 - y0, v2_z = z2 - z0;
            float nx = v1_y * v2_z - v1_z * v2_y; float ny = v1_z * v2_x - v1_x * v2_z; float nz = v1_x * v2_y - v1_y * v2_x;
            float n_len = std::sqrt(nx*nx + ny*ny + nz*nz);
            if (n_len > 0) { nx /= n_len; ny /= n_len; nz /= n_len; }
            float intensity = nx * sun_x + ny * sun_y + nz * sun_z;
            if (intensity < 0.0f) { intensity = 0.0f; }
            float final_light = 0.15f + intensity * 0.85f;
            glColor3f(0.55f * final_light, 0.42f * final_light, 0.28f * final_light);
            glVertex3f(x0, y0, z0); glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2);
            glVertex3f(x1, y1, z1); glVertex3f(x3, y3, z3); glVertex3f(x2, y2, z2);
        }
    }
    glEnd();
}
void DrawRealistic3DZombie() {
    glPushMatrix(); glTranslatef(2.5f, -1.2f, -4.0f);
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.1f, 0.1f); glVertex3f(-0.4f, 0.0f, 0.4f); glVertex3f(0.4f, 0.0f, 0.4f); glVertex3f(0.4f, 1.8f, 0.4f); glVertex3f(-0.4f, 1.8f, 0.4f);
    glColor3f(0.5f, 0.0f, 0.0f); glVertex3f(0.4f, 0.0f, 0.4f); glVertex3f(0.4f, 0.0f, -0.4f); glVertex3f(0.4f, 1.8f, -0.4f); glVertex3f(0.4f, 1.8f, 0.4f);
    glColor3f(1.0f, 0.3f, 0.3f); glVertex3f(-0.4f, 1.8f, 0.4f); glVertex3f(0.4f, 1.8f, 0.4f); glVertex3f(0.4f, 1.8f, -0.4f); glVertex3f(-0.4f, 1.8f, -0.4f);
    glEnd(); glPopMatrix();
}
void DrawFirstPersonM4Rifle(bool is_firing) {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    float wx = 0.30f; float wy = -0.32f; float wz = -0.55f;
    glBegin(GL_QUADS);
    glColor3f(0.20f, 0.21f, 0.24f); glVertex3f(wx + 0.0f, wy + 0.0f, wz); glVertex3f(wx + 0.32f, wy + 0.05f, wz); glVertex3f(wx + 0.28f, wy + 0.25f, wz); glVertex3f(wx + 0.0f, wy + 0.15f, wz);
    glColor3f(0.08f, 0.08f, 0.10f); glVertex3f(wx + 0.02f, wy + 0.12f, wz); glVertex3f(wx - 0.40f, wy + 0.18f, wz); glVertex3f(wx - 0.40f, wy + 0.21f, wz); glVertex3f(wx + 0.02f, wy + 0.14f, wz);
    glEnd();
    if (is_firing) {
        glBegin(GL_TRIANGLES); glColor3f(1.0f, 0.65f, 0.0f);
        glVertex3f(wx - 0.40f, wy + 0.195f, wz); glColor3f(1.0f, 0.95f, 0.0f);
        glVertex3f(wx - 0.60f, wy + 0.26f, wz); glVertex3f(wx - 0.55f, wy + 0.08f, wz);
        glEnd();
    }
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}
void DrawHUDCrosshairReticle() {
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 0.0f, 0.0f); glLineWidth(2.5f); glBegin(GL_LINES);
    glVertex2f(-0.025f, 0.0f); glVertex2f(0.025f, 0.0f); glVertex2f(0.0f, -0.04f); glVertex2f(0.0f, 0.04f); glEnd();
    glEnable(GL_DEPTH_TEST); glMatrixMode(GL_MODELVIEW); glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix();
}
int main() {
    NayderOpenGLRenderer engine_runtime; NayderAudioRuntime audio_system; NayderGameLoopClock engine_clock(107.0);
    glfwInit(); glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    GLFWwindow* active_window = glfwCreateWindow(1366, 768, "Neon Fall 17 v1.0.0", nullptr, nullptr);
    if (!active_window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(active_window); glfwSwapInterval(1);
    glfwSetInputMode(active_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Captures mouse natively
    glEnable(GL_DEPTH_TEST); glViewport(0, 0, 1366, 768);
    audio_system.InitializeAudioHardware();
    float cam_x = 0.0f, cam_y = 1.8f, cam_z = 8.0f; float yaw = -90.0f, pitch = 0.0f;
    bool fire_trigger_active = false; float flash_cooldown = 0.0f;
    double last_mx, last_my; glfwGetCursorPos(active_window, &last_mx, &last_my);
    while (!glfwWindowShouldClose(active_window)) {
        engine_clock.TickClockStart(); float dt = engine_clock.GetDeltaTime();
        double curr_mx, curr_my; glfwGetCursorPos(active_window, &curr_mx, &curr_my);
        float mouse_offset_x = (float)(curr_mx - last_mx); float mouse_offset_y = (float)(last_my - curr_my);         last_mx = curr_mx; last_my = curr_my;         float sensitivity = 0.15f; yaw += mouse_offset_x * sensitivity; pitch -= mouse_offset_y * sensitivity; // 360 MOUSE LOOK RE-CONNECTEDecho         double curr_mx, curr_my; glfwGetCursorPos(active_window, &curr_mx, &curr_my);         if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f;         float rad_yaw = yaw * (3.14159265f / 180.0f);         float forward_x = std::cos(rad_yaw); float forward_z = std::sin(rad_yaw);         float right_x = -std::sin(rad_yaw); float right_z = std::cos(rad_yaw);         float move_speed = 6.0f * dt;         if (glfwGetKey(active_window, GLFW_KEY_W) == GLFW_PRESS) { cam_x += forward_x * move_speed; cam_z += forward_z * move_speed; } // REAL TIME WASD RE-CONNECTED NATIVELYecho         double curr_mx, curr_my; glfwGetCursorPos(active_window, &curr_mx, &curr_my);         if (glfwGetKey(active_window, GLFW_KEY_S) == GLFW_PRESS) { cam_x -= forward_x * move_speed; cam_z -= forward_z * move_speed; }         if (glfwGetKey(active_window, GLFW_KEY_A) == GLFW_PRESS) { cam_x -= right_x * move_speed; cam_z -= right_z * move_speed; }         if (glfwGetKey(active_window, GLFW_KEY_D) == GLFW_PRESS) { cam_x += right_x * move_speed; cam_z += right_z * move_speed; }         int mouse_click = glfwGetMouseButton(active_window, GLFW_MOUSE_BUTTON_LEFT);         if (mouse_click == GLFW_PRESS) {             if (!fire_trigger_active) {                 fire_trigger_active = true; flash_cooldown = 0.07f;                 audio_system.PlayRealWavFile("Assets/Audio/weapon_fire.wav");                 pitch -= 1.6f; yaw += (std::sin(glfwGetTime() * 45.0f) * 0.4f);             }         } else { fire_trigger_active = false; }         if (flash_cooldown > 0.0f) flash_cooldown -= dt;         glClearColor(0.25f, 0.45f, 0.75f, 1.0f); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         SetupPerspectiveProjection(45.0f, 1366.0f / 768.0f, 0.1f, 150.0f);         ApplyFPSCameraView(cam_x, cam_y, cam_z, yaw, pitch);         DrawRealistic3DHeightmapTerrain();         DrawRealistic3DZombie();         DrawFirstPersonM4Rifle(flash_cooldown > 0.0f);         DrawHUDCrosshairReticle();         glfwSwapBuffers(active_window); engine_clock.SynchronizeFrameRateLock(); glfwPollEvents();     }     audio_system.TerminateAudioContext(); glfwDestroyWindow(active_window); glfwTerminate(); return 0; }
