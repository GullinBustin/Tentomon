#version 330 core
out vec4 color;

in vec3 UV;

uniform samplerCube renderedTexture;

void main()
{    
    color = texture(renderedTexture, UV);
}