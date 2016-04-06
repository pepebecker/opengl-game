//
//  Utils.hpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Camera.hpp"

namespace Utils {
    float toRadians(float angle);
    float mathPingPong(float min, float max, float t);
    glm::mat4 createViewMatrix(Camera *camera);
    glm::mat4 createViewMatrix(Camera *camera, glm::vec3 targetPostition);
    glm::mat4 createTransformationMatrix(glm::vec3 postition, glm::vec3 rotation, glm::vec3 scale);
    glm::mat4 createProjectionMatrix(GLfloat fieldOfView, GLfloat width, GLfloat height, GLfloat near_Plane, GLfloat far_plane, GLboolean ortho);
}

#endif /* PBUtils_hpp */
