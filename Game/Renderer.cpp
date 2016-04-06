//
//  Renderer.cpp
//  Game
//
//  Created by Pepe Becker on 3/7/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer(Camera *camera) {
    this->camera = camera;
    this->entities = std::vector<Entity *>();
    this->modelShader = new Shader("ModelShader.vs", "ModelShader.fs");
    
    float width = DisplayManager::getInstance().getWidth();
    float height = DisplayManager::getInstance().getHeight();
    this->projectionMatrix = Utils::createProjectionMatrix(FOV, width, height, NEAR_PLANE, FAR_PLANE, GL_FALSE);
    
    glm::mat4 guiProjectionMatrix = Utils::createProjectionMatrix(FOV, width, height, NEAR_PLANE, FAR_PLANE, GL_TRUE);
    
    guiRenderer = new GuiRenderer(guiProjectionMatrix);
}

void Renderer::render() {
    prepare();
    
    glm::mat4 viewMatrix = Utils::createViewMatrix(camera);
    
    for (Entity *entity : entities) {
        modelShader->start();
        modelShader->loadMatrix("projectionMatrix", projectionMatrix);
        modelShader->loadMatrix("viewMatrix", viewMatrix);
        modelShader->loadFloat("ambientLight", 0.5);
        
        bindEnity(entity);
        prepareEntity(entity);
        glDrawElements(GL_TRIANGLES, entity->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindEnity();
        
        modelShader->stop();
    }
    
    entities.clear();
    
    guiRenderer->render();
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(RED, GREEN, BLUE, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::bindEnity(Entity *entity) {
    glBindVertexArray(entity->getModel()->getVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->getModel()->getIndicesBuffer());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::unbindEnity() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::prepareEntity(Entity *entity) {
    glBindTexture(GL_TEXTURE_2D, entity->getTexture());
    modelShader->loadMatrix("transformationMatrix", entity->getTransformationMatrix());
}

void Renderer::addEntity(Entity *entity) {
    entities.push_back(entity);
}

void Renderer::addGui(GUI *gui) {
    guiRenderer->addGui(gui);
}

glm::mat4 Renderer::getProjectionMatrix() {
    return projectionMatrix;
}

Camera *Renderer::getCamera() {
    return camera;
}

Renderer::~Renderer() {
    delete modelShader;
    delete guiRenderer;
    Loader::getInstance().cleanup();
}

