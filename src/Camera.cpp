#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
        : position(glm::vec3(0.0f, 0.0f, 3.0f)),
          front(glm::vec3(0.0f, 0.0f, -1.0f)),
          up(glm::vec3(0.0f, 1.0f, 0.0f)),
          worldUp(up),
          yaw(-90.0f),
          pitch(0.0f),
          movementSpeed(4.5f),
          mouseSensitivity(0.1f)
{
    updateCameraVectors();
}

void Camera::update()
{
    // This method could be used for any continuous updates
    updateCameraVectors();
}

void Camera::processKeyboard(GLFWwindow *window, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * velocity;
}

void Camera::processMouse(float xOffset, float yOffset)
{
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getFront() const
{
    return front;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

void Camera::updateCameraVectors()
{
    glm::vec3 frontVec;
    frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVec.y = sin(glm::radians(pitch));
    frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontVec);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
