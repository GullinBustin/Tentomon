#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in mat4 aInstanceMatrix;

// Valores de salida ; serán interpolados para cada fragmento.

layout (std140) uniform Camera
{
    mat4 V;
    mat4 P;
};

out vec3 Normal;
out vec3 Position;
out vec2 UV;

void main()
{
	mat4 MVP = P*V*aInstanceMatrix;
    gl_Position = MVP * vec4(aPos,1);

	Position = vec3(aInstanceMatrix * vec4(aPos, 1));
	Normal = normalize(vec3(aInstanceMatrix * vec4(aNor, 0)));
	UV = vertexUV;
}
