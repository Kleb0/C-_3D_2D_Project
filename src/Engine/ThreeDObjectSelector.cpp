#include "Engine/ThreeDObjectSelector.hpp"
#include <glm/gtc/matrix_inverse.hpp>
#include <limits>
#include <iostream>

ThreeDObjectSelector::ThreeDObjectSelector()
{
}

void ThreeDObjectSelector::pickUpTarget(int mouseX, int mouseY, int screenWidth, int screenHeight, const glm::mat4 &view, const glm::mat4 &projection, const std::vector<ThreeDObject *> &objects)
{
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;

    glm::vec4 rayClip(x, y, -1.0f, 1.0f);
    glm::vec4 rayEye = glm::inverse(projection) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

    glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(view) * rayEye));
    glm::vec3 rayOrigin = glm::vec3(glm::inverse(view) * glm::vec4(0, 0, 0, 1));

    float closestDistance = std::numeric_limits<float>::max();
    ThreeDObject *closestObject = nullptr;

    for (auto *obj : objects)
    {
        if (!obj->isSelectable())
            continue;

        if (rayIntersectsCube(rayOrigin, rayWorld, *obj))
        {
            float distance = glm::length(obj->getPosition() - rayOrigin);
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestObject = obj;
            }
        }
    }

    selectedObject = closestObject;
}

bool ThreeDObjectSelector::rayIntersectsCube(const glm::vec3 &rayOrigin, const glm::vec3 &rayDir, const ThreeDObject &object)
{
    glm::mat4 invModel = glm::inverse(object.getModelMatrix());
    glm::vec3 localRayOrigin = glm::vec3(invModel * glm::vec4(rayOrigin, 1.0f));
    glm::vec3 localRayDir = glm::normalize(glm::vec3(invModel * glm::vec4(rayDir, 0.0f)));

    glm::vec3 min(-0.5f);
    glm::vec3 max(0.5f);

    float tmin = (min.x - localRayOrigin.x) / localRayDir.x;
    float tmax = (max.x - localRayOrigin.x) / localRayDir.x;
    if (tmin > tmax)
        std::swap(tmin, tmax);

    float tymin = (min.y - localRayOrigin.y) / localRayDir.y;
    float tymax = (max.y - localRayOrigin.y) / localRayDir.y;
    if (tymin > tymax)
        std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - localRayOrigin.z) / localRayDir.z;
    float tzmax = (max.z - localRayOrigin.z) / localRayDir.z;
    if (tzmin > tzmax)
        std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    return true;
}

void ThreeDObjectSelector::clearTarget()
{
    selectedObject = nullptr;
}

void ThreeDObjectSelector::select(ThreeDObject *object)
{
    selectedObject = object;
}