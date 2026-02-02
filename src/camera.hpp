#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;

    Camera(glm::vec3 startPos)
        : Position(startPos),
        Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
        Yaw(-90.0f),
        Pitch(0.0f),
        MovementSpeed(10.0f),
        MouseSensitivity(0.01f)
    {
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void CameraMove(Camera_Movement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;

        glm::vec3 flatFront = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z));

        if (direction == FORWARD)  Position += flatFront * velocity;
        if (direction == BACKWARD) Position -= flatFront * velocity;
        if (direction == LEFT)     Position -= Right * velocity;
        if (direction == RIGHT)    Position += Right * velocity;
        if (direction == UP)       Position += WorldUp * velocity;
        if (direction == DOWN)     Position -= WorldUp * velocity;
    }

    void CameraLook(float xoffset, float yoffset) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (Pitch > 89.0f)  Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;

        updateCameraVectors();
    }

private:
    void updateCameraVectors() {
        glm::vec3 f;
        f.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        f.y = sin(glm::radians(Pitch));
        f.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(f);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};