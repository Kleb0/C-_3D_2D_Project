#include "WorldObjects/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Camera::initialize()
{
}

void Camera::render(const glm::mat4 &)
{
}

Camera::Camera()
{
    setPosition(glm::vec3(5.0f, 10.0f, 10.0f));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(getPosition(), target, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

void Camera::zoom(float offset)
{
    std::cout << "[DEBUG] Zooming camera: " << offset << std::endl;
    fov -= offset * zoomSpeed;
    if (fov < 20.0f)
        fov = 20.0f;
    if (fov > 90.0f)
        fov = 90.0f;
}

void Camera::moveForward(float amount)
{
    glm::vec3 direction = glm::normalize(target - getPosition());
    glm::vec3 delta = direction * amount;

    setPosition(getPosition() + delta);
    setTarget(target + delta);

    std::cout << "[DEBUG] Moving camera: " << amount << std::endl;
}