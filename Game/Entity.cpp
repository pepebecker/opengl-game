//
//  Entity.cpp
//  Game
//
//  Created by Pepe Becker on 3/7/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(Model *model, GLuint texture, glm::vec3 position, glm::vec3 rotation, GLfloat scale) {
    this->model = model;
    this->texture = texture;
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    
    Loader::getInstance().loadToVAO(this->model, 3);
}

Entity::~Entity() {
    delete model;
}

