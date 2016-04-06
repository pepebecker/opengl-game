//
//  Renderer.hpp
//  Game
//
//  Created by Pepe Becker on 3/7/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <FreeImage.h>
#include "Entity.hpp"
#include "GUI.hpp"
#include "Utils.hpp"
#include "Shader.hpp"
#include "DisplayManager.hpp"
#include "Loader.hpp"
#include "GuiRenderer.hpp"

class Renderer {
private:
    std::vector<Entity *> entities;
    
    const float FOV = 70;
    const float NEAR_PLANE = 0.1;
    const float FAR_PLANE = 1000;
    
    const float RED = 0.1;
    const float GREEN = 0.1;
    const float BLUE = 0.1;
    
    GuiRenderer *guiRenderer;
    
    Camera *camera;
    
    Shader *modelShader;
    
    glm::mat4 projectionMatrix;
    
    void prepare();
    void bindEnity(Entity *entity);
    void unbindEnity();
    void prepareEntity(Entity *entity);
    
public:
    Renderer(Camera *camera);
    ~Renderer();
    void render();
    void addEntity(Entity *entity);
    void addGui(GUI *gui);
    
    glm::mat4 getProjectionMatrix();
    Camera *getCamera();
};

#endif /* Renderer_hpp */
