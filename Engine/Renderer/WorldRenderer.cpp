#include "WorldRenderer.h"
#include <GL/gl.h>
#include <iostream>
#include <cmath>

// Varyab global pou swiv deplasman kamera a an tan reyèl
float global_cam_x = 0.0f;
float global_cam_y = 1.8f; 
float global_cam_z = 8.0f;

void WorldRenderer::Initialize() {
    std::cout  8.0f) {
                    return (std::sin(px * 0.25f) * std::cos(pz * 0.25f) * 3.8f) - 0.5f;
                }
                return -1.0f;
            };

            float y0 = GetHeight(x0, z0); float y1 = GetHeight(x1, z1);
            float y2 = GetHeight(x2, z2); float y3 = GetHeight(x3, z3);

            float v1_x = x1 - x0, v1_y = y1 - y0, v1_z = z1 - z0;
            float v2_x = x2 - x0, v2_y = y2 - y0, v2_z = z2 - z0;
            float nx = v1_y * v2_z - v1_z * v2_y;
            float ny = v1_z * v2_x - v1_x * v2_z;
            float nz = v1_x * v2_y - v1_y * v2_x;
            float n_len = std::sqrt(nx*nx + ny*ny + nz*nz);
            if (n_len > 0) { nx /= n_len; ny /= n_len; nz /= n_len; }

            float intensity = nx * sun_x + ny * sun_y + nz * sun_z;
            if (intensity < 0.0f) intensity = 0.0f;
            float final_light = 0.18f + intensity * 0.82f;

            glColor3f(0.55f * final_light, 0.43f * final_light, 0.30f * final_light);
            glVertex3f(x0, y0, z0); glVertex3f(x1, y1, z1); glVertex3f(x2, y2, z2);
            glVertex3f(x1, y1, z1); glVertex3f(x3, y3, z3); glVertex3f(x2, y2, z2);
        }
    }
    glEnd();

    // 5. Desine modèl Brik Zonbi 3D Solid la
    glPushMatrix();
    glTranslatef(2.5f, -1.0f, -4.0f);
    glBegin(GL_QUADS);
        glColor3f(0.9f, 0.1f, 0.1f);
        glVertex3f(-0.4f, 0.0f,  0.4f); glVertex3f( 0.4f, 0.0f,  0.4f);
        glVertex3f( 0.4f, 1.8f,  0.4f); glVertex3f(-0.4f, 1.8f,  0.4f);
        glColor3f(0.5f, 0.0f, 0.0f);
        glVertex3f( 0.4f, 0.0f,  0.4f); glVertex3f( 0.4f, 0.0f, -0.4f);
        glVertex3f( 0.4f, 1.8f, -0.4f); glVertex3f( 0.4f, 1.8f,  0.4f);
        glColor3f(1.0f, 0.3f, 0.3f);
        glVertex3f(-0.4f, 1.8f,  0.4f); glVertex3f( 0.4f, 1.8f,  0.4f);
        glVertex3f( 0.4f, 1.8f, -0.4f); glVertex3f(-0.4f, 1.8f, -0.4f);
    glEnd();
    glPopMatrix();
}
