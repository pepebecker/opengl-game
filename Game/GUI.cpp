//
//  GUI.cpp
//  Game
//
//  Created by Pepe Becker on 3/16/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "GUI.hpp"

GUI::GUI(const GLchar *image, glm::vec2 position, glm::vec2 scale) {
    GLuint dimensions = 2;
    
    this->model = new Model({
        -1, +1,
        -1, -1,
        +1, +1,
        +1, -1
    }, {
        0, 1,
        0, 0,
        1, 1,
        1, 0
    });
    this->model->setVertexCount(this->model->getVerticesCount() / dimensions);
    this->texture = Loader::getInstance().loadTexture(image);
    this->position = position;
    this->scale = scale;
    this->rotation = 0;
    
    Loader::getInstance().loadToVAO(model, dimensions);
}

GUI::~GUI() {
    delete model;
}