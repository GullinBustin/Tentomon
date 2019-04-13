#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
//layout (location = 2) in vec2 vertexUV;

// Valores de salida ; serán interpolados para cada fragmento.
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;



out vec3 Normal;
out vec3 Position;

void main()
{
	mat4 MVP = P*V*M;
    gl_Position = MVP * vec4(aPos,1);

	Position = vec3(M * vec4(aPos, 1));
	Normal = vec3(M * vec4(aNor, 0));

//	float dirLightFactor = max(dot(vec3(M * vec4(aNor, 0)),dirLight), 0);
//	color = lightColor * ( 0.5 + dirLightFactor * 0.5) ;
}
