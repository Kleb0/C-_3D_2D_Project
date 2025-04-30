#pragma once

#include "WorldObjects/ThreeDObject.hpp"

class ImGuiGizmo
{
public:
    static void drawGizmo(const ThreeDObject *selectedObject);
};
