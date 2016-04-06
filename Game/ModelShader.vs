#version 400 core

in vec3 position;
in vec2 textureCoordinates;

out vec2 pass_textureCoordinates;
out vec4 worldPosition;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void) {
    worldPosition = transformationMatrix * vec4(position, 1.0);
    vec4 positionRelativeToCam = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * positionRelativeToCam;
    
    pass_textureCoordinates = textureCoordinates;
}