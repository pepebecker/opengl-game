//
//  DisplayManager.hpp
//  Game
//
//  Created by Pepe Becker on 3/4/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef DisplayManager_hpp
#define DisplayManager_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class DisplayManager {
private:
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    const int FPS = 120;
    
    GLFWwindow *window;
    long lastFrameTime;
    float delta;
    
    glm::vec2 previousMousePosition;
    
public:
    static DisplayManager &getInstance();
    
    void createDisplay();
    void prepareDisplay();
    void updateDisplay();
    float getDelta();
    bool displayShouldQuit();
    void closeDisplay();
    
    inline int getWidth() {
        return WIDTH;
    }
    
    inline int getHeight() {
        return HEIGHT;
    }
    
    inline glm::vec2 getMousePosition() {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            x = WIDTH / 2;
            y = HEIGHT / 2;
        }
        
        return glm::vec2(x, y);
    }
    
    inline glm::vec2 getMouseMotion() {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2(x, y) - previousMousePosition;
    }
    
    inline int getMouseButton(int button) {
        return glfwGetMouseButton(window, button);
    }
    
    inline void setMousePosition(double x, double y) {
        glfwSetCursorPos(window, x, y);
    }
    
    inline int getKey(GLuint key) {
        return glfwGetKey(window, key);
    }
    
    inline void hideMouse() {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    inline void showMouse() {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
    }
};

#endif /* DisplayManager_hpp */
