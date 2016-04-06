#version 400 core

in vec2 position;
in vec2 textureCoordinates;

out vec2 pass_textureCoordinates;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

void main(void) {
    gl_Position = projectionMatrix * transformationMatrix * vec4(position, -1, 1);
    
    pass_textureCoordinates = textureCoordinates;
}