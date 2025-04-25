#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <GL/gl.h>

class TwoDComponent
{
public:
    TwoDComponent(const std::string &imagePath);
    ~TwoDComponent();

    void render();

private:
    GLuint textureID = 0;
    int width = 0;
    int height = 0;

    void loadTexture(const std::string &imagePath);
};
