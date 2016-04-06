//
//  Model.hpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Templates.hpp"

class Model {
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> uvs;
    std::vector<GLuint> indices;
    
    size_t vertexCount;
    
    GLuint vao;
    GLuint indicesBuffer;
    std::vector<GLuint> vbos;
    
public:
    Model(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLuint> indices);
    Model(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs);
    Model(std::vector<GLfloat> vertices);
    Model();
    ~Model();
    
    std::vector<GLfloat> getVertices();
    void setVetices(GLfloat vertices[], GLsizei size);
    GLfloat *getVerticesPtr();
    GLsizei getVerticesSize();
    GLsizei getVerticesCount();
    
    std::vector<GLfloat> getUVs();
    void setUVs(std::vector<GLfloat> uvs);
    GLfloat *getUVsPtr();
    GLsizei getUVsSize();
    
    std::vector<GLuint> getIndices();
    void setIndices(std::vector<GLuint> indices);
    GLuint *getIndicesPtr();
    GLsizei getIndicesSize();
    
    GLsizei getVertexCount();
    void setVertexCount(size_t count);
    
    GLuint getVAO();
    void setVAO(GLuint vao);
    
    GLuint getIndicesBuffer();
    void setIndicesBuffer(GLuint vbo);
    
    void addVBO(GLuint vbo);
    
    virtual void buildModel();
    
    static Model *createPlane(glm::vec3 origion, glm::vec3 right, glm::vec3 up);
    
    
};

#endif /* Model_hpp */
