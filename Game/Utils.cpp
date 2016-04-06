//
//  Utils.cpp
//  Game
//
//  Created by Pepe Becker on 3/7/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "Utils.hpp"

float Utils::toRadians(float angle) {
    return angle * M_PI / 180;
}

float Utils::mathPingPong(float min, float max, float t) {
    float value;
    float range = max - min;
    
    if (t < 0.5f) {
        value = range * t * 2 + min;
    } else {
        value = range * (1 - t) * 2 + min;
    }
    
    return value;
}

glm::mat4 Utils::createViewMatrix(Camera *camera) {
    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::rotate(matrix, toRadians(camera->getRotation().x), glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, toRadians(camera->getRotation().y), glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, toRadians(camera->getRotation().z), glm::vec3(0, 0, 1));
    matrix = glm::translate(matrix, glm::vec3(-camera->getPosition().x, -camera->getPosition().y, -camera->getPosition().z));
    return matrix;
}

glm::mat4 Utils::createViewMatrix(Camera *camera, glm::vec3 targetPostition) {
    glm::mat4 matrix = glm::lookAt(camera->getPosition(), targetPostition, glm::vec3(0, 1, 0));
    return matrix;
}

glm::mat4 Utils::createTransformationMatrix(glm::vec3 postition, glm::vec3 rotation, glm::vec3 scale) {
    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::translate(matrix, glm::vec3(postition.x, postition.y, postition.z));
    matrix = glm::rotate(matrix, toRadians(rotation.x), glm::vec3(1, 0, 0));
    matrix = glm::rotate(matrix, toRadians(rotation.y), glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, toRadians(rotation.z), glm::vec3(0, 0, 1));
    matrix = glm::scale(matrix, scale);
    return matrix;
}

glm::mat4 Utils::createProjectionMatrix(GLfloat fieldOfView, GLfloat width, GLfloat height, GLfloat near_plane, GLfloat far_plane, GLboolean ortho) {
    if (ortho)
        return glm::ortho(-width / 100, width / 100, -height / 100, height / 100, near_plane, far_plane);
    
   return glm::perspective(fieldOfView, width / height, near_plane, far_plane);
}

