#version 400 core

in vec2 pass_textureCoordinates;

out vec4 out_Color;

uniform sampler2D textureSampler;

void main(void) {
    vec4 textureColor = texture(textureSampler, pass_textureCoordinates);
    
    textureColor.r = 1;
    textureColor.g = 1;
    textureColor.b = 1;
    
    out_Color = textureColor;
}