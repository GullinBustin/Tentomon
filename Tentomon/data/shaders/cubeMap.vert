#version 330 core
layout (location = 0) in vec3 aPos;

// Valores de salida ; serán interpolados para cada fragmento.
layout (std140) uniform Camera
{
    mat4 V;
    mat4 P;
};

out vec3 UV;

void main()
{
	mat4 MVP = P*V;
    gl_Position = P * (V * vec4(aPos, 0.0) + vec4(0,0,0,1));

	UV = aPos;
}
