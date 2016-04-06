//
//  Camera.hpp
//  Game
//
//  Created by Pepe Becker on 3/7/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "DisplayManager.hpp"

class Camera {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    
public:
    Camera(glm::vec3 position, glm::vec3 rotation);
    Camera();
    
    void update();
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    glm::vec3 getRotation();
    void setRotation(glm::vec3 rotation);
    void rotate(GLfloat x, GLfloat y, GLfloat z);
    void translate(GLfloat dx, GLfloat dy, GLfloat dz);
};

#endif /* Camera_hpp */
