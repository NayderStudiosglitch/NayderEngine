#include "WorldRenderer.h"

#include <GL/gl.h>
#include <iostream>

void WorldRenderer::Initialize()
{
    std::cout << "WORLD INITIALIZED\n";
}

void WorldRenderer::Render()
{
    glClearColor(0.35f,0.55f,0.90f,1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-20,20,-15,15,-50,50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //----------------------
    // GROUND
    //----------------------

    glColor3f(0.30f,0.22f,0.10f);

    glBegin(GL_QUADS);

    glVertex3f(-20,-10,0);
    glVertex3f( 20,-10,0);
    glVertex3f( 20,-15,0);
    glVertex3f(-20,-15,0);

    glEnd();

    //----------------------
    // MOUNTAIN
    //----------------------

    glColor3f(0.45f,0.34f,0.20f);

    glBegin(GL_TRIANGLES);

    glVertex3f(-15,-10,0);
    glVertex3f(-5,5,0);
    glVertex3f(5,-10,0);

    glEnd();

    //----------------------
    // ZOMBIE TEST
    //----------------------

    glColor3f(1,0,0);

    glBegin(GL_QUADS);

    glVertex3f(6,-10,0);
    glVertex3f(8,-10,0);
    glVertex3f(8,-3,0);
    glVertex3f(6,-3,0);

    glEnd();
}

