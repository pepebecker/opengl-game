//
//  GuiRenderer.hpp
//  Game
//
//  Created by Pepe Becker on 3/18/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef GuiRenderer_hpp
#define GuiRenderer_hpp

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

class GuiRenderer {
private:
    std::vector<GUI *> guis;
    
    Shader *shader;
    
    glm::mat4 projectionMatrix;
    
    void prepare();
    void bindGui(GUI *gui);
    void unbindGui();
    void prepareGui(GUI *gui);
    
public:
    GuiRenderer(glm::mat4 projectionMatrix);
    
    void render();
    void addGui(GUI *gui);
    void cleanup();
};

#endif /* GuiRenderer_hpp */
