//
//  main.cpp
//  Game
//
//  Created by Pepe Becker on 3/4/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "DisplayManager.hpp"
#include "Shader.hpp"
#include "Utils.hpp"
#include "Block.hpp"
#include "Renderer.hpp"
#include "MousePicker.hpp"
#include "Ray.hpp"

const GLuint world_width = 20;
const GLuint world_height = 10;
const GLuint world_lenght = 20;

GLuint woodTexture;
GLuint crateTexture;

bool mousePressed = false;
bool keyPressed = false;

enum GameState {
    Running,
    Paused,
    Cutscene
};

GameState gameSate;

GLint map[world_width][world_height][world_lenght];

std::vector<Entity *> entities;

void pauseGame() {
    DisplayManager::getInstance().showMouse();
    gameSate = Paused;
    
}

void resumeGame() {
    DisplayManager::getInstance().hideMouse();
    gameSate = Running;
}

bool blockAt(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0 || x >= world_width || y >= world_height || z >= world_lenght) {
        return false;
    }
    
    return map[x][y][z] > 0;
}

void configureFaces(Block *block, GLuint x, GLuint y, GLuint z) {
    if (blockAt(x + 1, y, z))
        block->hideFace(RIGHT_FACE);
    else
        block->showFace(RIGHT_FACE);
    
    if (blockAt(x - 1, y, z))
        block->hideFace(LEFT_FACE);
    else
        block->showFace(LEFT_FACE);
    
    if (blockAt(x, y + 1, z))
        block->hideFace(TOP_FACE);
    else
        block->showFace(TOP_FACE);
    
    if (blockAt(x, y - 1, z))
        block->hideFace(BOTTOM_FACE);
    else
        block->showFace(BOTTOM_FACE);
    
    if (blockAt(x, y, z + 1))
        block->hideFace(FRONT_FACE);
    else
        block->showFace(FRONT_FACE);
    
    if (blockAt(x, y, z - 1))
        block->hideFace(BACK_FACE);
    else
        block->showFace(BACK_FACE);
}

Entity *getBlock(GLuint x, GLuint y, GLuint z) {
    for (Entity *entity : entities) {
        if (entity->getPosition() == glm::vec3(x, y, z)) {
            return entity;
        }
    }
    
    return NULL;
}

void removeBlock(Entity *entity) {
    glm::vec3 pos = entity->getPosition();
    map[(int)pos.x][(int)pos.y][(int)pos.z] = 0;
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    
    for (Entity *entity : entities) {
        configureFaces((Block *) entity->getModel(), pos.x, pos.y, pos.z);
    }
}

void createWorldBlueprint() {
    for (GLuint x = 0; x < world_width; x++) {
        for (GLuint y = 0; y < world_height; y++) {
            for (GLuint z = 0; z < world_lenght; z++) {
                map[x][y][z] = 0;
                
                GLuint texture = woodTexture;
                
                if ((x % 2 == 1 && y % 2 == 0 && z % 2 == 0) ||
                    (x % 2 == 0 && y % 2 == 1 && z % 2 == 0) ||
                    (x % 2 == 0 && y % 2 == 0 && z % 2 == 1) ||
                    (x % 2 == 1 && y % 2 == 1 && z % 2 == 1)) {
                    texture = crateTexture;
                }
                
                map[0][y][z] = texture;
                map[x][0][z] = texture;
                map[x][y][0] = texture;
            }
        }
    }
}

void buildWorld() {
    for (GLuint x = 0; x < world_width; x++) {
        for (GLuint y = 0; y < world_height; y++) {
            for (GLuint z = 0; z < world_lenght; z++) {
                if (map[x][y][z] > 0) {
                    Block *block = new Block();
                    configureFaces(block, x, y, z);
                    block->buildModel();
                    entities.push_back(new Entity(block, map[x][y][z], glm::vec3(x, y, z), glm::vec3(0), 1));
                }
            }
        }
    }
}

int main(int argc, const char *argv[]) {
    if (glfwInit())
        printf("GLFW successfully initialized.\n");
    else
        exit(EXIT_FAILURE);
    
    DisplayManager::getInstance().createDisplay();
    
    glewExperimental = true;
    if (glewInit() == GLEW_OK)
        printf("GLEW successfully initialized.\n");
    else {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    woodTexture = Loader::getInstance().loadTexture("Wood.png");
    crateTexture = Loader::getInstance().loadTexture("Crate.png");
    
    createWorldBlueprint();
    
    buildWorld();
    
//    entities.push_back(new Entity(new Block(), crateTexture, glm::vec3(10, 5, 10), glm::vec3(0, 45, 0), 1));
    
    Camera *camera = new Camera(glm::vec3(world_width / 2, world_height / 2, world_lenght / 2 + 10), glm::vec3(0));
    
    Renderer *renderer = new Renderer(camera);
    
    GUI *gui = new GUI("Crosshair.png", glm::vec2(0, 0), glm::vec2(1));
    
    resumeGame();
    
    while (!DisplayManager::getInstance().displayShouldQuit())
    {
        DisplayManager::getInstance().prepareDisplay();
        
        if (DisplayManager::getInstance().getMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
            if (mousePressed == false) {
                glm::vec2 mousePos = DisplayManager::getInstance().getMousePosition();
                Ray ray = MousePicker::screenToWorldRay(renderer, mousePos.x, mousePos.y, 100);
                
                if (Entity *target = Ray::getClosestEntityFromRay(ray, entities)) {
//                    removeBlock(target);
                    if (target->getTexture() == woodTexture) {
                        target->setTexture(crateTexture);
                    } else {
                        target->setTexture(woodTexture);
                    }
                }
            }
            
            mousePressed = true;
        } else {
            mousePressed = false;
        }
        
        if (DisplayManager::getInstance().getKey(GLFW_KEY_ESCAPE)) {
            if (!keyPressed) {
                if (gameSate == Paused) {
                    resumeGame();
                } else {
                    pauseGame();
                }
            }
            
            keyPressed = true;
        } else {
            keyPressed = false;
        }
        
        if (gameSate == Running) {
            camera->update();
        }
        
        for (Entity *entity : entities) {
            renderer->addEntity(entity);
        }
        
        renderer->addGui(gui);
        
        renderer->render();
        
        DisplayManager::getInstance().updateDisplay();
    }
    
    entities.clear();
    delete camera;
    delete renderer;
    Loader::getInstance().cleanup();

    DisplayManager::getInstance().closeDisplay();
    glfwTerminate();
    return EXIT_SUCCESS;
}
