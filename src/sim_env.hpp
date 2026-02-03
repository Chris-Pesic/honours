#pragma once
#include "sphere.hpp"
#include "texture.hpp"
#include "baseGrid.hpp"
#include "shader.hpp"

baseGrid grid;

Shader* gridShader = nullptr;
Shader* sphereShader = nullptr;

Sphere* planet = nullptr;
unsigned int earthTexture = 0;

bool simLoaded = false;

void LoadGrid() {
    if (simLoaded) {
        return;
    }
    grid.Create(2000.0f, 100);
    gridShader = new Shader("res/shaders/grid.vert", "res/shaders/grid.frag");

    planet = new Sphere(6.37f, 36, 18);
    sphereShader = new Shader("res/shaders/sphere.vert", "res/shaders/sphere.frag");
    earthTexture = LoadTexture2D("res/textures/earth.jpg");

    simLoaded = true;
    std::cout << "Simulation Environment Loaded.\n";
}

template <class Camera>
void RenderSim(GLFWwindow* window, Camera& camera) {

    if (!gridShader || !sphereShader || !planet || earthTexture == 0) {
        LoadGrid();
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int fbW, fbH;
    glfwGetFramebufferSize(window, &fbW, &fbH);
    if (fbH == 0) fbH = 1;

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)fbW / (float)fbH,
        0.1f,
        1000.0f
    );

    gridShader->use();
    gridShader->setMat4("view", glm::value_ptr(view));
    gridShader->setMat4("projection", glm::value_ptr(projection));
    grid.Render(gridShader->ID, view, projection);

    sphereShader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, earthTexture);
    sphereShader->setInt("planetTexture", 0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0, 0, 0));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));

    sphereShader->setMat4("model", glm::value_ptr(model));
    sphereShader->setMat4("view", glm::value_ptr(view));
    sphereShader->setMat4("projection", glm::value_ptr(projection));

    planet->Draw();
}