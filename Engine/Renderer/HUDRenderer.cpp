#include "HUDRenderer.h"
#include <iostream>
#include <GLFW/glfw3.h>

NayderHUDRenderer::NayderHUDRenderer() {}

void NayderHUDRenderer::SetOrthographicProjection() {
    // 🎛️ Reset projection matrix vectors to enforce 2D screen coordinate parameters
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1366, 0, 768, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST); // Disable depth buffering so UI overlays sit on top of 3D meshes
}

void NayderHUDRenderer::RenderHUDDashboard(const HUDLiveStats& stats) {
    // =============================================================================
    // 🎯 MODULE v0.3.7: NATIVE GRAPHICAL CROSSHAIR DRAW (Screen Center)
    // =============================================================================
    float cx = 1366.0f / 2.0f;
    float cy = 768.0f / 2.0f;
    float size = 10.0f;

    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 0.0f, 0.0f); // Bright Red Crosshair Reticle
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Horizontal line
        glVertex2f(cx - size, cy);
        glVertex2f(cx + size, cy);
        // Vertical line
        glVertex2f(cx, cy - size);
        glVertex2f(cx, cy + size);
    glEnd();

    // =============================================================================
    // 🟩 NATIVE GRAPHICAL HEALTH BAR POLYGON RASTERIZATION
    // =============================================================================
    float bar_x = 50.0f;
    float health_y = 50.0f;
    float bar_height = 20.0f;
    float max_bar_width = 200.0f;
    
    // Scale length multiplier live based on player health percentage
    float health_pct = static_cast<float>(stats.current_hp) / static_cast<float>(stats.max_hp);
    float active_health_width = max_bar_width * health_pct;

    // Draw Health Bar Background (Dark Matte)
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(bar_x, health_y);
        glVertex2f(bar_x + max_bar_width, health_y);
        glVertex2f(bar_x + max_bar_width, health_y + bar_height);
        glVertex2f(bar_x, health_y + bar_height);
    glEnd();

    // Draw Active Health Bar Foreground (Neon Green)
    glColor3f(0.0f, 1.0f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(bar_x, health_y);
        glVertex2f(bar_x + active_health_width, health_y);
        glVertex2f(bar_x + active_health_width, health_y + bar_height);
        glVertex2f(bar_x, health_y + bar_height);
    glEnd();

    // =============================================================================
    // 🟦 NATIVE GRAPHICAL ARMOR BAR POLYGON RASTERIZATION
    // =============================================================================
    float armor_y = 20.0f;
    float armor_pct = static_cast<float>(stats.current_armor) / static_cast<float>(stats.max_armor);
    float active_armor_width = max_bar_width * armor_pct;

    // Draw Armor Bar Background (Dark Matte)
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(bar_x, armor_y);
        glVertex2f(bar_x + max_bar_width, armor_y);
        glVertex2f(bar_x + max_bar_width, armor_y + bar_height);
        glVertex2f(bar_x, armor_y + bar_height);
    glEnd();

    // Draw Active Armor Bar Foreground (Cyan Blue)
    glColor3f(0.0f, 0.7f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(bar_x, armor_y);
        glVertex2f(bar_x + active_armor_width, armor_y);
        glVertex2f(bar_x + active_armor_width, armor_y + bar_height);
        glVertex2f(bar_x, armor_y + bar_height);
    glEnd();

    // Fallback status prints to ensure logging cycles trace metrics seamlessly
    std::cout << " 📺 [GRAPHICAL HUD MATRIX TICK]: Crosshair and Vertex Bars rasterized cleanly to display context! FPS: " << stats.current_fps << std::endl;
}

void NayderHUDRenderer::RestorePerspectiveProjection() {
    glEnable(GL_DEPTH_TEST);
    
    // Pop matrices to completely restore 3D perspective camera space view attributes
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
