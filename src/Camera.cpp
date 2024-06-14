#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera() : position(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f),
                   yaw(-90.0f), pitch(0.0f), movementSpeed(2.5f), mouseSensitivity(0.1f)
{}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(GLFWwindow *window, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        moveUp(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        moveDown(deltaTime);
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

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
}

void Camera::moveUp(float deltaTime)
{
    position.y += movementSpeed * deltaTime; // Move up along the Y-axis
}

void Camera::moveDown(float deltaTime)
{
    position.y -= movementSpeed * deltaTime; // Move down along the Y-axis
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

glm::vec3 Camera::getFront() const
{
    return front;
}
