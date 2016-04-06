//
//  Model.cpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "Model.hpp"

Model::Model(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLuint> indices) {
    this->vertices = vertices;
    this->uvs = uvs;
    this->indices = indices;
    this->vertexCount = indices.size();
}

Model::Model(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs) {
    this->vertices = vertices;
    this->uvs = uvs;
}

Model::Model(std::vector<GLfloat> vertices) {
    this->vertices = vertices;
    this->uvs = {
        0, 0,
        1, 0,
        1, 1,
        0, 1,
    };
}

Model::Model() {
    Model *model = createPlane(glm::vec3(-1), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
    this->vertices = model->getVertices();
    this->uvs = model->getUVs();
    this->indices = model->getIndices();
    this->vertexCount = model->getIndices().size();
}

std::vector<GLfloat> Model::getVertices() {
    return this->vertices;
}

void Model::setVetices(GLfloat _vertices[], GLsizei size) {
    this->vertices.clear();
    for (GLuint i = 0; i < size; i++) {
        this->vertices.push_back(_vertices[i]);
    }
}

GLfloat *Model::getVerticesPtr() {
    return &this->vertices[0];
}

GLsizei Model::getVerticesSize() {
    return (GLsizei) this->vertices.size() * sizeof(GLfloat);
}

GLsizei Model::getVerticesCount() {
    return (GLsizei) this->vertices.size();
}

std::vector<GLfloat> Model::getUVs() {
    return this->uvs;
}

void Model::setUVs(std::vector<GLfloat> uvs) {
    this->uvs = uvs;
}

GLfloat *Model::getUVsPtr() {
    return &this->uvs[0];
}

GLsizei Model::getUVsSize() {
    return (GLsizei) this->uvs.size() * sizeof(GLfloat);
}

std::vector<GLuint> Model::getIndices() {
    return this->indices;
}

void Model::setIndices(std::vector<GLuint> indices) {
    this->indices = indices;
}

GLuint *Model::getIndicesPtr() {
    return &this->indices[0];
}

GLsizei Model::getIndicesSize() {
    return (GLsizei) this->indices.size() * sizeof(GLuint);
}

GLsizei Model::getVertexCount() {
    return (GLsizei) this->vertexCount;
}

void Model::setVertexCount(size_t count) {
    this->vertexCount = count;
}

GLuint Model::getVAO() {
    return vao;
}

void Model::setVAO(GLuint vao) {
    this->vao = vao;
}

GLuint Model::getIndicesBuffer() {
    return indicesBuffer;
}

void Model::setIndicesBuffer(GLuint vbo) {
    this->indicesBuffer = vbo;
}

void Model::addVBO(GLuint vbo) {
    this->vbos.push_back(vbo);
}

Model::~Model() {
    this->vertices.clear();
    this->normals.clear();
    this->uvs.clear();
    this->indices.clear();
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &indicesBuffer);
    for (GLuint vbo : vbos) {
        glDeleteBuffers(1, &vbo);
    }
}

void Model::buildModel() {
    
}

Model *Model::createPlane(glm::vec3 origion, glm::vec3 right, glm::vec3 up) {
    std::vector<GLfloat> vertices {
        origion.x,
        origion.y,
        origion.z,
        
        origion.x + right.x,
        origion.y + right.y,
        origion.z + right.z,
        
        origion.x + right.x + up.x,
        origion.y + right.y + up.y,
        origion.z + right.z + up.z,
        
        origion.x + up.x,
        origion.y + up.y,
        origion.z + up.z,
        
    };
    
    std::vector<GLfloat> uvs {
        0, 0,
        1, 0,
        1, 1,
        0, 1,
    };
    
    std::vector<GLuint> indices {
        0, 1, 2,
        2, 3, 0,
    };
    
    return new Model(vertices, uvs, indices);
}
