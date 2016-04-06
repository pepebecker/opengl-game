//
//  Loader.hpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <FreeImage.h>
#include "Model.hpp"

class Loader {
private:
    std::vector<GLuint> textures;
    
    GLuint createVAO();
    void unbindVAO();
    GLuint bindIndices(GLsizei indicesSize, GLuint *indices);
    GLuint storeDataInAttributeList(GLuint attributeNumber, GLint coordinateSize, GLsizei dataSize, GLfloat *data);
    
public:
    static Loader &getInstance();
    
    GLuint loadTexture(const GLchar *filename);
    
    void loadToVAO(Model *model, GLuint dimensions);
    
    void cleanup();
};

#endif /* Loader_hpp */
