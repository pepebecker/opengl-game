//
//  ModelShader.cpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include "ModelShader.hpp"

ModelShader::ModelShader() : ShaderProgram("Model.vs", "Model.fs") {
    vertexShaderID = loadShader("Model.vs", GL_VERTEX_SHADER);
    fragmentShaderID = loadShader("Model.fs", GL_FRAGMENT_SHADER);
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    bindAttributes();
    glLinkProgram(programID);
    glValidateProgram(programID);
    getAllUniformLocations();
}

void ModelShader::bindAttributes() {
    ShaderProgram::bindAttribute(0, "position");
    ShaderProgram::bindAttribute(1, "textureCoordinates");
    ShaderProgram::bindAttribute(2, "normal");
}

void ModelShader::getAllUniformLocations() {
    
}