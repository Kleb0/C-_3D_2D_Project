#pragma once
#include "Engine/ThreeDSceneDrawer.hpp"
#include "WorldObjects/ThreedObject.hpp"

class OpenGLContext
{
public:
    OpenGLContext();
    ~OpenGLContext() = default;

    void initialize();
    void resize(int w, int h);
    void render();
    GLuint getTexture() const { return fboTexture; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void add(ThreeDObject &object);

private:
    GLuint fbo = 0;
    GLuint fboTexture = 0;
    GLuint rbo = 0;
    int width = 800;
    int height = 600;

    ThreeDSceneDrawer scene;
};