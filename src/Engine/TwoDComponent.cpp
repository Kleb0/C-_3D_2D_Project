#include "Engine/TwoDComponent.hpp"
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <iostream>
#include <filesystem>

TwoDComponent::TwoDComponent(const std::string &imagePath)
{
    std::cout << "[DEBUG] Loading texture as 2D component front following path : " << imagePath << std::endl;
    loadTexture(imagePath);
}

TwoDComponent::~TwoDComponent()
{
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}

void TwoDComponent::loadTexture(const std::string &imagePath)
{
    SDL_Surface *loadedSurface = IMG_Load(imagePath.c_str());
    if (!loadedSurface)
    {
        std::cerr << "Error during image loading " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA32, 0);

    if (!formattedSurface)
    {
        std::cerr << "Error during image conversion: " << SDL_GetError() << std::endl;
        return;
    }

    width = formattedSurface->w;
    height = formattedSurface->h;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(formattedSurface);
    SDL_FreeSurface(loadedSurface);

    std::cout << "Texture loaded: " << imagePath << " (" << width << "x" << height << ")" << std::endl;
}

void TwoDComponent::render()
{
    if (textureID == 0)
        return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPushMatrix();
    glTranslatef(2.5f, 0.f, 2.5f);
    glRotatef(180.f, 180.f, 1.f, 0.f);

    float h = 4.0f;
    float w = (static_cast<float>(width) / height) * h;

    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 0.f);
    glVertex3f(-w / 2, -h / 2, 0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex3f(w / 2, -h / 2, 0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex3f(w / 2, h / 2, 0.f);
    glTexCoord2f(0.f, 1.f);
    glVertex3f(-w / 2, h / 2, 0.f);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}