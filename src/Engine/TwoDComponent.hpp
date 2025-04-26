#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <glad/glad.h>

class TwoDComponent
{
public:
    TwoDComponent(const std::string &imagePath);
    ~TwoDComponent();

    void render();

private:
    GLuint textureID = 0;
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    int width = 0;
    int height = 0;

    void loadTexture(const std::string &imagePath);
    void setupMesh();
};
