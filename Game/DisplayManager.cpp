//
//  DisplayManager.cpp
//  Game
//
//  Created by Pepe Becker on 3/4/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "DisplayManager.hpp"

DisplayManager &DisplayManager::getInstance() {
    static DisplayManager instance;
    return instance;
}

void DisplayManager::createDisplay() {
    glfwWindowHint (GLFW_SAMPLES, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "Pepe's Game", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    glfwSwapInterval(1);
    
    glViewport(0, 0, WIDTH, HEIGHT);
    lastFrameTime = glfwGetTime();
}

void DisplayManager::prepareDisplay() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void DisplayManager::updateDisplay() {
    delta = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();
    
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    previousMousePosition = glm::vec2(x, y);
}

float DisplayManager::getDelta() {
    return delta;
}

bool DisplayManager::displayShouldQuit() {
    return glfwWindowShouldClose(window);
}

void DisplayManager::closeDisplay() {
    glfwDestroyWindow(window);
}