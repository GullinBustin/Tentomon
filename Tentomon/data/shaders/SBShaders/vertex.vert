#version 450 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(){
    
    mat4 MVP = P*V*M;
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
}