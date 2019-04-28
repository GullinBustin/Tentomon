#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;

void main(){
    float depth = texture( renderedTexture, UV).x;
	depth = pow(depth, 24);
	color = vec3(depth, depth, depth);
}