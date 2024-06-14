#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    glm::mat4 getViewMatrix() const;

    void processKeyboard(GLFWwindow *window, float deltaTime);

    void processMouse(float xOffset, float yOffset);

    void moveUp(float deltaTime); // Add this method to move up along the Y-axis
    void moveDown(float deltaTime); // Add this method to move down along the Y-axis
    glm::vec3 getPosition() const;

    glm::vec3 getFront() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
};

#endif // CAMERA_H
