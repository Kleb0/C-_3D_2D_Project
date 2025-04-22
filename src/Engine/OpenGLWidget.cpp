#include "Engine/OpenGLWidget.hpp"
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <cmath>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    connect(&timer, &QTimer::timeout, this, QOverload<>::of(&OpenGLWidget::update));
    timer.start(16); // environ 60 FPS
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::initializeGL()
{
    qDebug() << "OpenGL initialized";
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{

    qDebug() << "Painting...";

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    float t = colorShift;

    glBegin(GL_TRIANGLES);

    auto colorPulse = [](float base)
    {
        glColor3f(
            0.5f + 0.5f * sin(base),
            0.5f + 0.5f * sin(base + 2.0f),
            0.5f + 0.5f * sin(base + 4.0f));
    };

    // FACE AVANT
    colorPulse(t);
    glVertex3f(0, 0, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);

    colorPulse(t + 0.5f);
    glVertex3f(0, 0, 0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, 0.5f);

    colorPulse(t + 1.0f);
    glVertex3f(0, 0, 0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    colorPulse(t + 1.5f);
    glVertex3f(0, 0, 0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    colorPulse(t + 2.0f);
    glVertex3f(0, 0, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);

    colorPulse(t + 2.5f);
    glVertex3f(0, 0, -0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);

    colorPulse(t + 3.0f);
    glVertex3f(0, 0, -0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    colorPulse(t + 3.5f);
    glVertex3f(0, 0, -0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // FACE DESSUS
    colorPulse(t + 4.0f);
    glVertex3f(0, 0.5f, 0);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);

    colorPulse(t + 4.5f);
    glVertex3f(0, 0.5f, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);

    colorPulse(t + 5.0f);
    glVertex3f(0, 0.5f, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    colorPulse(t + 5.5f);
    glVertex3f(0, 0.5f, 0);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    colorPulse(t + 6.0f);
    glVertex3f(0, -0.5f, 0);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);

    colorPulse(t + 6.5f);
    glVertex3f(0, -0.5f, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);

    colorPulse(t + 7.0f);
    glVertex3f(0, -0.5f, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    colorPulse(t + 7.5f);
    glVertex3f(0, -0.5f, 0);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    colorPulse(t + 8.0f);
    glVertex3f(0.5f, 0, 0);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);

    colorPulse(t + 8.5f);
    glVertex3f(0.5f, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);

    colorPulse(t + 9.0f);
    glVertex3f(0.5f, 0, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);

    colorPulse(t + 9.5f);
    glVertex3f(0.5f, 0, 0);
    glColor3f(1, 0, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);

    colorPulse(t + 10.0f);
    glVertex3f(-0.5f, 0, 0);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    colorPulse(t + 10.5f);
    glVertex3f(-0.5f, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    colorPulse(t + 11.0f);
    glVertex3f(-0.5f, 0, 0);
    glColor3f(0, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    colorPulse(t + 11.5f);
    glVertex3f(-0.5f, 0, 0);
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();

    angle += 0.5f;
    colorShift += 0.1f;
}
