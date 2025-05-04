#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include "WorldObjects/ThreeDObject.hpp"

class SimiliGizmo
{
public:
    ThreeDObject *getTarget() const { return target; }
    void setTarget(ThreeDObject *object);
    void drawInfo();
    void disable();
    bool hasTarget() const { return target != nullptr; }

private:
    void initialize();

    ThreeDObject *target = nullptr;
    bool initialized = false;
};
