//
//  MousePicker.cpp
//  Game
//
//  Created by Pepe Becker on 3/11/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "MousePicker.hpp"

MousePicker::MousePicker(Camera *camera, glm::mat4 projectionMatrix) {
    this->camera = camera;
    this->projectionMatrix = projectionMatrix;
    this->viewMatrix = Utils::createViewMatrix(camera);
}

glm::vec3 MousePicker::getCurrentRay() {
    return currentRay;
}

void MousePicker::update(double mouseX, double mouseY) {
    viewMatrix = Utils::createViewMatrix(camera);
    currentRay = calculateMouseRay();
    this->mouseX = mouseX;
    this->mouseY = mouseY;
}

glm::vec3 MousePicker::calculateMouseRay() {
    glm::vec2 normalizeCoords = toNormalizedDeviceSpace(mouseX, mouseY);
    glm::vec4 clipCoords = glm::vec4(normalizeCoords.x, normalizeCoords.y, -1, 1);
    glm::vec4 eyeCoords = toEyeSpace(clipCoords);
    glm::vec3 worldRay = toWorldSpace(eyeCoords);
    return worldRay;
}

glm::vec3 MousePicker::toWorldSpace(glm::vec4 eyeCoords) {
    glm::mat4 invertedView = glm::inverse(viewMatrix);
    glm::vec4 rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
    mouseRay = glm::normalize(mouseRay);
    return mouseRay;
}

glm::vec4 MousePicker::toEyeSpace(glm::vec4 clipCoords) {
    glm::mat4 invertedProjection = glm::inverse(projectionMatrix);
    glm::vec4 eyeCoords = invertedProjection * clipCoords;
    return glm::vec4(eyeCoords.x, eyeCoords.y, -1, 0);
}

glm::vec2 MousePicker::toNormalizedDeviceSpace(float mouseX, float mouseY) {
    float width = DisplayManager::getInstance().getWidth();
    float height = DisplayManager::getInstance().getHeight();
    
    float x = (2 * mouseX) / width - 1;
    float y = 1 - (2 * mouseY) / height;

    return glm::vec2(x, y);
}

Ray MousePicker::screenToWorldRay(Renderer *renderer, double mouseX, double mouseY, float distance) {
    // Normalized Device Space
    float width = DisplayManager::getInstance().getWidth();
    float height = DisplayManager::getInstance().getHeight();
    float x = (2 * mouseX) / width - 1;
    float y = 1 - (2 * mouseY) / height;
    
    // Clip Space
    glm::vec4 clipCoords = glm::vec4(x, y, -1, 1);
    
    // Eye Space
    glm::mat4 invertedProjection = glm::inverse(renderer->getProjectionMatrix());
    glm::vec4 eyeCoords = invertedProjection * clipCoords;
    eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1, 0);
    
    // World Space
    glm::mat4 invertedView = glm::inverse(Utils::createViewMatrix(renderer->getCamera()));
    glm::vec4 rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
    mouseRay = glm::normalize(mouseRay);
    
    Ray ray = Ray(renderer->getCamera()->getPosition(), mouseRay, distance);
    
    return ray;
}


