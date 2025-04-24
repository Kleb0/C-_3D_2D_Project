#include "Engine/ThreeDWorldView.hpp"
#include <GL/glu.h>

ThreeDWorldView::ThreeDWorldView(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void ThreeDWorldView::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ThreeDWorldView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, float(w) / float(h), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void ThreeDWorldView::paintGL()
{
    scene.render();
}
