#include <glad/glad.h>
#include "UI/SimiliGizmo.hpp"
#include "imgui.h"
#include "ImGuizmo.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <filesystem>

void SimiliGizmo::setTarget(ThreeDObject *object)
{
    target = object;
    if (object)
    {
        std::cout << "[SIMILI_GIZMO] Target set to object at position: "
                  << object->getPosition().x << ", "
                  << object->getPosition().y << ", "
                  << object->getPosition().z << std::endl;
    }
}

void SimiliGizmo::initialize()
{
    if (initialized)
        return;

    std::cout << "[SIMILI_GIZMO] Initialization complete." << std::endl;

    initialized = true;
}

void SimiliGizmo::render(const glm::mat4 &view, const glm::mat4 &projection, const ImVec2 &pos, const ImVec2 &size)
{
    if (!target)
        return;

    initialize();

    ImGuizmo::BeginFrame();

    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);

    glm::mat4 objectMatrix = glm::mat4(1.0f);
    objectMatrix = glm::translate(objectMatrix, target->getPosition());

    ImGuizmo::Manipulate(
        glm::value_ptr(view),
        glm::value_ptr(projection),
        ImGuizmo::TRANSLATE,
        ImGuizmo::WORLD,
        glm::value_ptr(objectMatrix));

    if (ImGuizmo::IsUsing())
    {
        glm::vec3 newPos = glm::vec3(objectMatrix[3]);
        target->setPosition(newPos);
    }
}
