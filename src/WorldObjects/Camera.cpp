#include "WorldObjects/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

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
    glm::vec3 pos = getPosition();
    return glm::lookAt(pos, glm::vec3(2.5f, 0.0f, 2.5f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}