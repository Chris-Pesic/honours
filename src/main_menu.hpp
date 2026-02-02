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
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        screen = 1;
    }
}