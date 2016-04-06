//
//  Camera.cpp
//  Game
//
//  Created by Pepe Becker on 3/7/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "Camera.hpp"
#include "Utils.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 rotation) {
    this->position = position;
    this->rotation = rotation;
}

Camera::Camera() {
    this->position = glm::vec3(0);
    this->rotation = glm::vec3(0);
}

void Camera::update() {
    glm::vec2 mousePos = DisplayManager::getInstance().getMouseMotion();
    rotate(mousePos.y * 0.1f, mousePos.x * 0.1f, 0);
    
    GLfloat speed = 0.1;
    
    glm::vec3 input(0);
    
    if (DisplayManager::getInstance().getKey(GLFW_KEY_A) || DisplayManager::getInstance().getKey(GLFW_KEY_LEFT)) {
        input.x --;
    }
    
    if (DisplayManager::getInstance().getKey(GLFW_KEY_D) || DisplayManager::getInstance().getKey(GLFW_KEY_RIGHT)) {
        input.x ++;
    }
    
    if (DisplayManager::getInstance().getKey(GLFW_KEY_W) || DisplayManager::getInstance().getKey(GLFW_KEY_UP)) {
        input.z ++;
    }
    
    if (DisplayManager::getInstance().getKey(GLFW_KEY_S) || DisplayManager::getInstance().getKey(GLFW_KEY_DOWN)) {
        input.z --;
    }
    
    if (DisplayManager::getInstance().getKey(GLFW_KEY_SPACE)) {
        input.y ++;
    }
    
    if (DisplayManager::getInstance().getKey(GLFW_KEY_LEFT_SHIFT) || DisplayManager::getInstance().getKey(GLFW_KEY_RIGHT_SHIFT)) {
        input.y --;
    }
    
    glm::vec3 movement(0);
    
    movement.x += input.x * sin(Utils::toRadians(rotation.y + 90));
    movement.z -= input.x * cos(Utils::toRadians(rotation.y + 90));
    
    movement.y = input.y;
    
    movement.x += input.z * sin(Utils::toRadians(rotation.y));
    movement.z -= input.z * cos(Utils::toRadians(rotation.y));
    
    if (glm::length(movement) > 0) {
        movement /= glm::length(movement);
    }
    
    translate(movement.x * speed, movement.y * speed, movement.z * speed);
    
//    look hole in shader
}

glm::vec3 Camera::getPosition() {
    return position;
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

glm::vec3 Camera::getRotation() {
    return rotation;
}

void Camera::setRotation(glm::vec3 rotation) {
    this->rotation = rotation;
}

void Camera::rotate(GLfloat x, GLfloat y, GLfloat z) {
    rotation.x += x;
    rotation.y += y;
    rotation.z += z;
}

void Camera::translate(GLfloat dx, GLfloat dy, GLfloat dz) {
    position.x += dx;
    position.y += dy;
    position.z += dz;
}