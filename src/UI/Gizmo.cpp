#include "UI/Gizmo.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <filesystem>

void Gizmo::setTarget(ThreeDObject *object)
{
    std::cout << "[GIZMO] Target set to object at position: "
              << object->getPosition().x << ", "
              << object->getPosition().y << ", "
              << object->getPosition().z << std::endl;

    target = object;
    axes[0] = glm::vec3(1, 0, 0);
    axes[1] = glm::vec3(0, 1, 0);
    axes[2] = glm::vec3(0, 0, 1);
}

void Gizmo::initialize()
{
    if (initialized)
        return;

    std::filesystem::path shaderBase = std::filesystem::current_path().parent_path() / "src" / "UI";
    std::string vertPath = (shaderBase / "gizmo.vert").string();
    std::string fragPath = (shaderBase / "gizmo.frag").string();

    std::cout << "[DEBUG] Vertex Shader Path: " << vertPath << std::endl;
    std::cout << "[DEBUG] Fragment Shader Path: " << fragPath << std::endl;

    gizmoShader = GizmoShader(vertPath, fragPath);

    float axisVertices[] = {
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    initialized = true;
}

void Gizmo::render(const glm::mat4 &view, const glm::mat4 &projection)
{
    if (!target)
        return;

    initialize();

    glm::vec3 currentPos = target->getPosition();
    static glm::vec3 lastRenderedPos = glm::vec3(-9999.0f);

    if (currentPos != lastRenderedPos)
    {
        std::cout << "[GIZMO] Rendering Gizmo at position: "
                  << currentPos.x << ", "
                  << currentPos.y << ", "
                  << currentPos.z << std::endl;
        lastRenderedPos = currentPos;
    }

    glm::mat4 model = glm::translate(glm::mat4(1.0f), currentPos);
    glm::mat4 mvp = projection * view * model;

    gizmoShader.use();
    gizmoShader.setMat4("uMVP", mvp);

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}
