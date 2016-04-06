//
//  Loader.cpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "Loader.hpp"

Loader &Loader::getInstance() {
    static Loader instance;
    return instance;
}

GLuint Loader::loadTexture(const GLchar *filename) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    FIBITMAP *bitmap;
    
    // Get the format of the image file
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename, 0);
    
    // If the format can't be determined, try to guess the format from the file name
    if(fif == FIF_UNKNOWN) {
        fif = FreeImage_GetFIFFromFilename(filename);
    }
    
    // Load the data in bitmap if possible
    if(fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) {
        bitmap = FreeImage_Load(fif, filename);
    } else {
        bitmap = NULL;
    }
    
    // PROCESS IMAGE if bitmap was successfully initialized
    if(bitmap) {
        unsigned int w = FreeImage_GetWidth(bitmap);
        unsigned int h = FreeImage_GetHeight(bitmap);
        unsigned pixel_size = FreeImage_GetBPP(bitmap);
        
        // Get a pointer to the pixel data
        BYTE *data = (BYTE*)FreeImage_GetBits(bitmap);
        
        // Process only RGB and RGBA images
        if(pixel_size == 24) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, (GLvoid*)data);
        }
        else if (pixel_size == 32) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)data);
        }
        else {
            std::cerr << "pixel size = " << pixel_size << " don't know how to process this case. I'm out!" << std::endl;
            exit(-1);
        }
        
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    textures.push_back(texture);
    
    return texture;
}

GLuint Loader::createVAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::loadToVAO(Model *model, GLuint dimensions) {
    model->setVAO(createVAO());
    model->setIndicesBuffer(bindIndices(model->getIndicesSize(), model->getIndicesPtr()));
    model->addVBO(storeDataInAttributeList(0, dimensions,  model->getVerticesSize(), model->getVerticesPtr()));
    model->addVBO(storeDataInAttributeList(1, 2, model->getUVsSize(), model->getUVsPtr()));
    unbindVAO();
}

GLuint Loader::bindIndices(GLsizei indicesSize, GLuint *indices) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return vbo;
}

GLuint Loader::storeDataInAttributeList(GLuint attributeNumber, GLint coordinateSize, GLsizei dataSize, GLfloat *data) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

void Loader::cleanup() {
    for (GLuint texture : textures) {
        glDeleteTextures(1, &texture);
    }
}
