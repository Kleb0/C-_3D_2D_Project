#pragma once

#include "WorldObjects/ThreeDObject.hpp"
#include <vector>

class ThreeDObjectSelector
{
public:
    ThreeDObjectSelector();
    void update(int mouseX, int mouseY, int screenWidth, int screenHeight, const glm::mat4 &view, const glm::mat4 &projection, const std::vector<ThreeDObject *> &objects);
    void select(ThreeDObject *object);

    ThreeDObject *getSelectedObject() const { return selectedObject; }

private:
    ThreeDObject *selectedObject = nullptr;

    bool rayIntersectsCube(const glm::vec3 &rayOrigin, const glm::vec3 &rayDir, const ThreeDObject &object);
};
