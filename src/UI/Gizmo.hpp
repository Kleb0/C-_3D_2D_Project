#pragma once

#include <glm/glm.hpp>
#include "WorldObjects/ThreeDObject.hpp"
#include "UI/GizmoShader.hpp"

class Gizmo
{
public:
    void setTarget(ThreeDObject *object);
    void render(const glm::mat4 &view, const glm::mat4 &projection);
    void updateInteraction(const glm::vec3 &rayOrigin, const glm::vec3 &rayDir);

private:
    void initialize();

    ThreeDObject *target = nullptr;
    glm::vec3 axes[3];

    unsigned int vao = 0;
    unsigned int vbo = 0;
    bool initialized = false;

    GizmoShader gizmoShader;

    int hoveredAxis = -1;
    bool dragging = false;
    glm::vec3 dragStartPos;
};
