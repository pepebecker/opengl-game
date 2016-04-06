//
//  GUI.hpp
//  Game
//
//  Created by Pepe Becker on 3/16/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef GUI_hpp
#define GUI_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Model.hpp"
#include "Utils.hpp"
#include "Loader.hpp"

class GUI {
    Model *model;
    GLuint texture;
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;
    
public:
    GUI(const GLchar *image, glm::vec2 position, glm::vec2 scale);
    ~GUI();
    
    Model *getModel() {
        return model;
    }
    
    GLuint getTexture() {
        return texture;
    }
    
    glm::vec2 getPosition() {
        return position;
    }
    
    GLfloat getRotation() {
        return rotation;
    }
    
    glm::vec2 getScale() {
        return scale;
    }
    
    glm::mat4 getTransformationMatrix() {
        glm::vec3 pos = glm::vec3(getPosition(), -1);
        glm::vec3 rot = glm::vec3(0, 0, getRotation());
        glm::vec3 scl = glm::vec3(getScale(), 1);
        return Utils::createTransformationMatrix(pos, rot, scl);
    }
};

#endif /* GUI_hpp */
