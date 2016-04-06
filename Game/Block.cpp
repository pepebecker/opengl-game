//
//  Block.cpp
//  Game
//
//  Created by Pepe Becker on 3/9/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "Block.hpp"

Block::Block() : Model() {    
    for (GLuint i = 0; i < 6; i++) {
        drawFace[i] = GL_TRUE;
    }
    
    buildModel();
}

void Block::buildModel() {
    std::vector<Model *> sides;
    if (drawFace[RIGHT_FACE])
        sides.push_back(Model::createPlane(glm::vec3( .5, -.5,  .5), glm::vec3( 0,  0, -1), glm::vec3( 0,  1,  0))); // Right
    if (drawFace[LEFT_FACE])
        sides.push_back(Model::createPlane(glm::vec3(-.5, -.5, -.5), glm::vec3( 0,  0,  1), glm::vec3( 0,  1,  0))); // Left
    if (drawFace[BOTTOM_FACE])
        sides.push_back(Model::createPlane(glm::vec3(-.5, -.5, -.5), glm::vec3( 1,  0,  0), glm::vec3( 0,  0,  1))); // Bottom
    if (drawFace[TOP_FACE])
        sides.push_back(Model::createPlane(glm::vec3(-.5,  .5,  .5), glm::vec3( 1,  0,  0), glm::vec3( 0,  0, -1))); // Top
    if (drawFace[BACK_FACE])
        sides.push_back(Model::createPlane(glm::vec3( .5, -.5, -.5), glm::vec3(-1,  0,  0), glm::vec3( 0,  1,  0))); // Back
    if (drawFace[FRONT_FACE])
        sides.push_back(Model::createPlane(glm::vec3(-.5, -.5,  .5), glm::vec3( 1,  0,  0), glm::vec3( 0,  1,  0))); // Front
    
    std::vector<GLfloat> vertices;
    for (std::vector<Model *>::size_type i = 0; i != sides.size(); i++) {
        vertices += sides[i]->getVertices();
    }
    
    std::vector<GLfloat> uvs {
        0, 0,
        1, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 1,
    };
    
    std::vector<GLuint> indices;
    GLuint index = 0;
    size_t vertexCount = 0;
    for (std::vector<Model *>::size_type i = 0; i != sides.size() * 6; i += 6) {
        indices.push_back(index + 0);
        indices.push_back(index + 1);
        indices.push_back(index + 2);
        indices.push_back(index + 2);
        indices.push_back(index + 3);
        indices.push_back(index + 0);
        index += 4;
        vertexCount += 6;
    }
    
    this->vertices = vertices;
    this->uvs = uvs;
    this->indices = indices;
    this->vertexCount = vertexCount;
    
    vertices.clear();
    uvs.clear();
    indices.clear();
}

void Block::showFace(GLuint face) {
    drawFace[face] = GL_TRUE;
}

void Block::hideFace(GLuint face) {
    drawFace[face] = GL_FALSE;
}
