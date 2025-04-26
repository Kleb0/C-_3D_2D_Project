#include "Engine/TwoDComponent.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

unsigned int textureShaderProgram = 0;

const char *textureVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 model;
uniform mat4 viewProj;
out vec2 TexCoord;
void main()
{
    gl_Position = viewProj * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";

const char *textureFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;
void main()
{
    FragColor = texture(texture1, TexCoord);
}
)";

void compileTextureShaders()
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &textureVertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &textureFragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    textureShaderProgram = glCreateProgram();
    glAttachShader(textureShaderProgram, vertexShader);
    glAttachShader(textureShaderProgram, fragmentShader);
    glLinkProgram(textureShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

TwoDComponent::TwoDComponent(const std::string &imagePath)
{
    loadTexture(imagePath);
    setupMesh();
}

TwoDComponent::~TwoDComponent()
{
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
}

void TwoDComponent::loadTexture(const std::string &imagePath)
{
    SDL_Surface *loadedSurface = IMG_Load(imagePath.c_str());
    if (!loadedSurface)
    {
        std::cerr << "Error during image loading: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(loadedSurface);

    if (!formattedSurface)
    {
        std::cerr << "Error during image format conversion: " << SDL_GetError() << std::endl;
        return;
    }

    width = formattedSurface->w;
    height = formattedSurface->h;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, formattedSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(formattedSurface);
}

void TwoDComponent::setupMesh()
{
    if (textureShaderProgram == 0)
        compileTextureShaders();

    float quadVertices[] = {
        // positions          // texcoords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void TwoDComponent::render()
{
    if (textureID == 0)
        return;

    glUseProgram(textureShaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.5f, 0.0f, 2.5f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation sur l'axe X
    model = glm::scale(model, glm::vec3(4.0f, 4.0f * height / (float)width, 1.0f));

    glm::mat4 view = glm::lookAt(
        glm::vec3(5.0f, 10.0f, 10.0f),
        glm::vec3(2.5f, 0.0f, 2.5f),
        glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 viewProj = proj * view;

    unsigned int modelLoc = glGetUniformLocation(textureShaderProgram, "model");
    unsigned int viewProjLoc = glGetUniformLocation(textureShaderProgram, "viewProj");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewProjLoc, 1, GL_FALSE, glm::value_ptr(viewProj));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(textureShaderProgram, "texture1"), 0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
