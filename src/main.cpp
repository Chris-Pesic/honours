#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "baseGrid.h"
#include "Camera.h"
#include "Sphere.h"

Camera camera(glm::vec3(0.0f, 3.0f, 8.0f));
baseGrid grid;

Shader* gridShader = nullptr;
Shader* sphereShader = nullptr;

Sphere* planet = nullptr;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400, lastY = 300;
bool rotatingCamera = false;
bool cameraSnap = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!rotatingCamera)
    {
        lastX = xpos;
        lastY = ypos;
        cameraSnap = true;
        return;
    }

    if (cameraSnap)
    {
        lastX = xpos;
        lastY = ypos;
        cameraSnap = false;
        return;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.CameraLook(xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Load()
{
    grid.Create(5000.0f, 100);
    gridShader = new Shader("res/shaders/grid.vert", "res/shaders/grid.frag");

    planet = new Sphere(10.0f, 36, 18);
    sphereShader = new Shader("res/shaders/sphere.vert", "res/shaders/sphere.frag");
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.CameraMove(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.CameraMove(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.CameraMove(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.CameraMove(RIGHT, deltaTime);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (!rotatingCamera)
        {
            rotatingCamera = true;
            cameraSnap = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    else
    {
        if (rotatingCamera)
        {
            rotatingCamera = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Render(GLFWwindow* window)
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        1000.0f
    );

    gridShader->use();
    gridShader->setMat4("view", glm::value_ptr(view));
    gridShader->setMat4("projection", glm::value_ptr(projection));
    grid.Render(gridShader->ID, view, projection);

    sphereShader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 0, 0));

    sphereShader->setMat4("model", glm::value_ptr(model));
    sphereShader->setMat4("view", glm::value_ptr(view));
    sphereShader->setMat4("projection", glm::value_ptr(projection));
    sphereShader->setVec3("color", 0.4f, 0.7f, 1.0f);

    planet->Draw();
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Honours Project", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glEnable(GL_DEPTH_TEST);

    Load();

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(window);
        Render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}