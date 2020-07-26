#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in mat4 aInstanceMatrix;


layout (std140) uniform Camera
{
    mat4 V;
    mat4 P;
};

void main()
{
    gl_Position = P * V  * aInstanceMatrix * vec4(aPos, 1.0f); 
}