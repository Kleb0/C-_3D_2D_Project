#include <QCoreApplication>
#include "SDL2Widget.hpp"
#include <QDebug>
#include <QOpenGLFunctions>
#include <GL/gl.h>

SDL2Widget::SDL2Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

SDL2Widget::~SDL2Widget()
{
    if (textureId != 0)
        glDeleteTextures(1, &textureId);

    if (imageSurface)
        SDL_FreeSurface(imageSurface);
}

void SDL2Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0, 0, 0, 1);

    QString imagePath = QCoreApplication::applicationDirPath() + "/../assets/images/cat.png";
    imageSurface = IMG_Load(imagePath.toStdString().c_str());

    if (!imageSurface)
    {
        qDebug() << "Failed to load image:" << IMG_GetError();
        return;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    GLint mode = imageSurface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, mode, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void SDL2Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
}

void SDL2Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!textureId)
        return;

    glBindTexture(GL_TEXTURE_2D, textureId);

    int w = width();
    int h = height();

    int imgW = imageSurface->w;
    int imgH = imageSurface->h;

    int x = (w - imgW) / 2;
    int y = (h - imgH) / 2;

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(x, y);
    glTexCoord2f(1, 0);
    glVertex2f(x + imgW, y);
    glTexCoord2f(1, 1);
    glVertex2f(x + imgW, y + imgH);
    glTexCoord2f(0, 1);
    glVertex2f(x, y + imgH);
    glEnd();
}
