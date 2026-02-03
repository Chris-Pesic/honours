#pragma once
#include <GLFW/glfw3.h>

struct Keybinds {
    int forward = GLFW_KEY_W;
    int backward = GLFW_KEY_S;
    int left = GLFW_KEY_A;
    int right = GLFW_KEY_D;
    int up = GLFW_KEY_E;
    int down = GLFW_KEY_Q;
    int rotate_cam = GLFW_MOUSE_BUTTON_RIGHT;
    int exit = GLFW_KEY_ESCAPE;
};

template <class Camera>
void InputManager(GLFWwindow* window, Camera& camera, float deltaTime, bool& rotatingCamera, const Keybinds& keybinds) {

    if (glfwGetKey(window, keybinds.forward) == GLFW_PRESS) {
        camera.CameraMove(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, keybinds.backward) == GLFW_PRESS) {
        camera.CameraMove(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, keybinds.left) == GLFW_PRESS) {
        camera.CameraMove(LEFT, deltaTime);
    }

    if (glfwGetKey(window, keybinds.right) == GLFW_PRESS) {
        camera.CameraMove(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, keybinds.up) == GLFW_PRESS) {
        camera.CameraMove(UP, deltaTime);
    }

    if (glfwGetKey(window, keybinds.down) == GLFW_PRESS) {
        camera.CameraMove(DOWN, deltaTime);
    }


    if (glfwGetMouseButton(window, keybinds.rotate_cam) == GLFW_PRESS) {
        if (!rotatingCamera)
        {
            rotatingCamera = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            double x, y;
            glfwGetCursorPos(window, &x, &y);
        }
    }
    else {
        if (rotatingCamera) {
            rotatingCamera = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    if (glfwGetKey(window, keybinds.exit) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}