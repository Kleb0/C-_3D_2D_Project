#include "Engine/ThreeDSceneDrawer.hpp"
#include <GL/gl.h>
#include <GL/glu.h>

ThreeDSceneDrawer::ThreeDSceneDrawer() {}

void ThreeDSceneDrawer::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    drawBackgroundGradient();
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    gluLookAt(5, 10, 10, 2.5, 0, 2.5, 0, 1, 0);
    drawGrid();
}

void ThreeDSceneDrawer::drawGrid()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i <= 5; ++i)
    {
        glVertex3f(0, 0, i);
        glVertex3f(5, 0, i);
        glVertex3f(i, 0, 0);
        glVertex3f(i, 0, 5);
    }
    glEnd();
}

void ThreeDSceneDrawer::drawBackgroundGradient()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);

    glColor3f(0.05f, 0.05f, 0.05f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);

    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
