#pragma once

#include <string>
#include "WorldObjects/ThreedObject.hpp"

class Camera : public ThreeDObject
{
public:
    Camera();
    void initialize() override;
    void render(const glm::mat4 &viewProj) override;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;
    std::string getName() const { return "MainCamera"; }

    glm::vec3 target = glm::vec3(2.5f, 0.0f, 2.5f);
    void setTarget(const glm::vec3 &newTarget) { target = newTarget; }
    glm::vec3 getTarget() const { return target; }

    bool isSoftwareCamera() const { return true; }
    bool isAGameCamera() const { return false; }
    bool isSelectable() const override { return !isSoftwareCamera(); }

    void zoom(float offset);
    void moveForward(float amount);

    float fov = 45.0f;
    float nearClip = 0.1f;
    float farClip = 100.0f;
    float zoomSpeed = 0.1f;
    float zommFactor = 1.0f;
};
