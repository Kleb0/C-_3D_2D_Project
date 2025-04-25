#include "Engine/ThreeDSceneDrawer.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include "Engine/TwoDComponent.hpp"
#include <iostream>
#include <filesystem>

TwoDComponent *imageComponent = nullptr;

ThreeDSceneDrawer::ThreeDSceneDrawer() {}

void ThreeDSceneDrawer::initialization()
{
    std::filesystem::path rootPath = std::filesystem::current_path().parent_path();
    std::string imagePath = (rootPath / "assets/images/cat.png").string();

    std::cout << "[DEBUG] Répertoire courant : " << std::filesystem::current_path() << std::endl;
    std::cout << "[DEBUG] Chemin construit : " << imagePath << std::endl;

    imageComponent = new TwoDComponent(imagePath);
}

void ThreeDSceneDrawer::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    drawBackgroundGradient();
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    gluLookAt(5, 10, 10, 2.5, 0, 2.5, 0, 1, 0);
    drawGrid();

    if (imageComponent)
    {
        imageComponent->render();
    }
    else
    {
        std::cerr << "Image component not initialized." << std::endl;
    }
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
