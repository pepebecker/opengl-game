//
//  Ray.hpp
//  Game
//
//  Created by Pepe Becker on 3/11/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"
#include "Utils.hpp"
#include "Entity.hpp"

class Ray {
private:
    glm::vec3 origin;
    glm::vec3 direction;
    float distance;
    
public:
    Ray(glm::vec3 origin, glm::vec3 direction, float distance);
    
    glm::vec3 getOrigin();
    glm::vec3 getDirection();
    float getDistance();
    
    static bool testRayOBBIntersection(Ray ray, glm::vec3 aabb_min, glm::vec3 aabb_max, glm::mat4 ModelMatrix/*, float &intersection_distance*/);
    static Entity *getClosestEntityFromRay(Ray ray, std::vector<Entity *> entities);
};

#endif /* Ray_hpp */
