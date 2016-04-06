//
//  Shader.hpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader {
private:
    GLuint programID;
    
public:
    Shader(const GLchar *vertexFile, const GLchar *fragmentFile);
    ~Shader();
    
    void start();
    void stop();
    
    void loadInt(const GLchar *uniformName, GLint value);
    void loadFloat(const GLchar *uniformName, GLfloat value);
    void loadMatrix(const GLchar *uniformName, glm::mat2 matrix);
    void loadMatrix(const GLchar *uniformName, glm::mat3 matrix);
    void loadMatrix(const GLchar *uniformName, glm::mat4 matrix);
};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif  /* Shader_hpp */
