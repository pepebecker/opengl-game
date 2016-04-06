//
//  GuiRenderer.cpp
//  Game
//
//  Created by Pepe Becker on 3/18/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "GuiRenderer.hpp"

GuiRenderer::GuiRenderer(glm::mat4 projectionMatrix) {
    this->projectionMatrix = projectionMatrix;
    this->guis = std::vector<GUI *>();
    
    this->shader = new Shader("GUIShader.vs", "GUIShader.fs");
    
//    std::vector<GLfloat> vertices {-1, 1, -1, -1, 1, 1, 1, -1};
}

void GuiRenderer::render() {
    prepare();
    
    for (GUI *gui : guis) {
        shader->start();
        shader->loadMatrix("projectionMatrix", projectionMatrix);
        
        bindGui(gui);
        prepareGui(gui);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, gui->getModel()->getVertexCount());
        unbindGui();
        
        shader->stop();
    }

    guis.clear();
}

void GuiRenderer::prepare() {
    glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
}

void GuiRenderer::bindGui(GUI *gui) {
    glBindVertexArray(gui->getModel()->getVAO());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GuiRenderer::unbindGui() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void GuiRenderer::prepareGui(GUI *gui) {
    glBindTexture(GL_TEXTURE_2D, gui->getTexture());
    shader->loadMatrix("transformationMatrix", gui->getTransformationMatrix());
}

void GuiRenderer::addGui(GUI *gui) {
    guis.push_back(gui);
}

void GuiRenderer::cleanup() {
    delete shader;
    guis.clear();
}