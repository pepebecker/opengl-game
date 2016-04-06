//
//  Entity.hpp
//  Game
//
//  Created by Pepe Becker on 3/7/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Model.hpp"
#include "Utils.hpp"
#include <vector>
#include "Loader.hpp"

class Entity {
private:
    Model *model;
    GLuint texture;
    glm::vec3 position;
    glm::vec3 rotation;
    GLfloat scale;
    
public:
    Entity(Model *model, GLuint texture, glm::vec3 position, glm::vec3 rotation, GLfloat scale);
    ~Entity();
    
    Model *getModel() {
        return model;
    }
    
    GLuint getTexture() {
        return texture;
    }
    
    void setTexture(GLuint texture) {
        this->texture = texture;
    }
    
    glm::vec3 getPosition() {
        return position;
    }
    
    glm::vec3 getRotation() {
        return rotation;
    }
    
    GLfloat getScale() {
        return scale;
    }
    
    glm::mat4 getTransformationMatrix() {
        return Utils::createTransformationMatrix(getPosition(), getRotation(), glm::vec3(getScale()));
    }
    
    void rotate(GLfloat x, GLfloat y, GLfloat z) {
        rotation.x += x;
        rotation.y += y;
        rotation.z += z;
    }
    
    void translate(GLfloat dx, GLfloat dy, GLfloat dz) {
        position.x += dx;
        position.y += dy;
        position.z += dz;
    }
};

#endif /* Entity_hpp */
