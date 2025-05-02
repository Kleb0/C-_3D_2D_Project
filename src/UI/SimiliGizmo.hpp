#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include "WorldObjects/ThreeDObject.hpp"

class SimiliGizmo
{
public:
    void setTarget(ThreeDObject *object);
    void render(const glm::mat4 &view, const glm::mat4 &projection, const ImVec2 &pos, const ImVec2 &size);

private:
    void initialize();

    ThreeDObject *target = nullptr;
    bool initialized = false;
};
