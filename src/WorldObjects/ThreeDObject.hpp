#pragma once

#include <glm/glm.hpp>

class ThreeDObject
{
public:
    ThreeDObject();
    ~ThreeDObject();

    void initialize();
    void render(const glm::mat4 &viewProj);
    glm::vec3 getPosition() const { return position; }
    void setPosition(const glm::vec3 &pos) { position = pos; }

private:
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int shaderProgram = 0;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0.0f);
    void compileShaders();
};