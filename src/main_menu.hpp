#pragma once
#include <iostream>

bool menuLoaded = false;

extern int screen;

void LoadMenu() {
    if (menuLoaded) {
        return;
    }
    std::cout << "Main Menu Loaded.\n";
    std::cout << "Press 'R' to load a simulation.\n";
    menuLoaded = true;
}

void RenderMenu(GLFWwindow* window) {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        screen = 1;
    }
}

void UnloadMenu() {
    if (!menuLoaded) {
        return;
    }
    std::cout << "Main Menu Unloaded.\n";
    menuLoaded = false;
}