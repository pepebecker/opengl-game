//
//  MousePicker.hpp
//  Game
//
//  Created by Pepe Becker on 3/11/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef MousePicker_hpp
#define MousePicker_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"
#include "Utils.hpp"
#include "Ray.hpp"
#include "Renderer.hpp"

class MousePicker {
private:
    glm::vec3 currentRay;
    
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    Camera *camera;
    
    glm::vec3 calculateMouseRay();
    glm::vec2 toNormalizedDeviceSpace(float mouseX, float mouseY);
    glm::vec4 toEyeSpace(glm::vec4 clipCoords);
    glm::vec3 toWorldSpace(glm::vec4 eyeCoords);
    
    double mouseX = 0, mouseY = 0;
    
public:
    MousePicker(Camera *camera, glm::mat4 projectionMatrix);
    
    glm::vec3 getCurrentRay();
    
    void update(double mouseX, double mouseY);
    
    static Ray screenToWorldRay(Renderer *renderer, double mouse_x, double mouse_y, float distance);
};

#endif /* MousePicker_hpp */
