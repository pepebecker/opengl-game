#version 400 core

in vec2 pass_textureCoordinates;
in vec4 worldPosition;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform float ambientLight;

const int inverseColor = 0;

void main(void) {
    vec4 color = vec4(pass_textureCoordinates.x, 1 - pass_textureCoordinates.x, pass_textureCoordinates.y, 1.0);
    
    color = texture(textureSampler, pass_textureCoordinates);
    
    float brightness = 0;
    
    color = max(color * brightness, color * ambientLight);
    
    float distance = length(worldPosition.xz - vec2(10, 10)) / 10;
    
//    if (distance < 2) {
//        color.a = distance;
//    } else {
//        color.a = 1;
//    }
    
    
    if (inverseColor > 0) {
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
    
    color.a = 1;
    
    out_Color = color;
}