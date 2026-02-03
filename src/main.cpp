#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "baseGrid.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "texture.hpp"
#include "input.hpp"
#include "sim_env.hpp"
#include "main_menu.hpp"

Keybinds keybinds;
Camera camera(glm::vec3(0.0f, 1.0f, 20.0f));

//Time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Camera
float lastX = 400;
float lastY = 400;
bool rotatingCamera = false;

//Screen State
int screen = 0;

//Camera Rotation
void MouseCam(GLFWwindow* window, double xpos, double ypos){
    if (!rotatingCamera){
        lastX = (float)xpos;
        lastY = (float)ypos;
        return;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.CameraLook(xoffset, yoffset);
}

void WindowSize(GLFWwindow* window, int width, int height){
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Honours Project", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";

        return -1;
    }

    glfwSetFramebufferSizeCallback(window, WindowSize);
    glfwSetCursorPosCallback(window, MouseCam);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        InputManager(window, camera, deltaTime, rotatingCamera, keybinds);

        switch (screen) {

        case 0:
            //  Main Menu
            LoadMenu();
            RenderMenu(window);
            break;

        case 1:
            //  Simulation Environment
            UnloadMenu();
            LoadGrid();
            RenderSim(window, camera);
            break;

        case 2:
            //  Settings
            break;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}