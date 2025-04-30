#include "Engine/ThreeDObjectSelector.hpp"
#include <glm/gtc/matrix_inverse.hpp>
#include <limits>
#include <iostream>

ThreeDObjectSelector::ThreeDObjectSelector()
{
}

void ThreeDObjectSelector::update(int mouseX, int mouseY, int screenWidth, int screenHeight, const glm::mat4 &view, const glm::mat4 &projection, const std::vector<ThreeDObject *> &objects)
{
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;

    glm::vec4 rayClip(x, y, -1.0f, 1.0f);
    glm::vec4 rayEye = glm::inverse(projection) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

    glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(view) * rayEye));
    glm::vec3 rayOrigin = glm::vec3(glm::inverse(view)[3]);

    std::cout << "[DEBUG] Ray origin: " << rayOrigin.x << ", " << rayOrigin.y << ", " << rayOrigin.z << std::endl;
    std::cout << "[DEBUG] Ray dir: " << rayWorld.x << ", " << rayWorld.y << ", " << rayWorld.z << std::endl;

    float closestDistance = std::numeric_limits<float>::max();
    ThreeDObject *closestObject = nullptr;

    for (auto *obj : objects)
    {
        std::cout << "[DEBUG] Testing object at: "
                  << obj->getPosition().x << ", "
                  << obj->getPosition().y << ", "
                  << obj->getPosition().z << std::endl;

        if (rayIntersectsCube(rayOrigin, rayWorld, *obj))
        {
            std::cout << "[DEBUG] → Intersection détectée avec objet à "
                      << obj->getPosition().x << ", "
                      << obj->getPosition().y << ", "
                      << obj->getPosition().z << std::endl;
        }
        else
        {
            std::cout << "[DEBUG] → Aucune intersection avec objet à "
                      << obj->getPosition().x << ", "
                      << obj->getPosition().y << ", "
                      << obj->getPosition().z << std::endl;
        }
    }

    selectedObject = closestObject;
}

bool ThreeDObjectSelector::rayIntersectsCube(const glm::vec3 &rayOrigin, const glm::vec3 &rayDir, const ThreeDObject &object)
{
    glm::vec3 min = object.getPosition() - glm::vec3(0.5f);
    glm::vec3 max = object.getPosition() + glm::vec3(0.5f);

    float tmin = (min.x - rayOrigin.x) / rayDir.x;
    float tmax = (max.x - rayOrigin.x) / rayDir.x;
    if (tmin > tmax)
        std::swap(tmin, tmax);

    float tymin = (min.y - rayOrigin.y) / rayDir.y;
    float tymax = (max.y - rayOrigin.y) / rayDir.y;
    if (tymin > tymax)
        std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - rayOrigin.z) / rayDir.z;
    float tzmax = (max.z - rayOrigin.z) / rayDir.z;
    if (tzmin > tzmax)
        std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    return true;
}
