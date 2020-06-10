#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) out vec4 normal;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;

layout (std140) uniform Light
{
    vec3 lightColor;
    vec3 dirLight;
	vec3 pointLight;
};

void main()
{
	float specularMaterial = 1.0f;
	float specularPow = 32;

	vec3 pointLightDir = normalize(Position - pointLight);
	vec3 viewDir = normalize(Position - cameraPos);

	float dirLightDiffuse = max(dot(Normal,-dirLight), 0);
	vec3 dirReflectDir = reflect(dirLight, Normal);
	float dirLightSpecular = pow(max(dot(-viewDir, dirReflectDir), 0.0), specularPow);
	float dirColor = dirLightDiffuse + dirLightSpecular * specularMaterial;

	float pointDiffuse = max(dot(Normal,-pointLightDir), 0);
	vec3 pointReflectDir = reflect(pointLightDir, Normal);
	float pointSpecular = pow(max(dot(viewDir, -pointReflectDir), 0.0), specularPow);
	float pointColor = pointDiffuse + pointSpecular * specularMaterial;
	color = vec4(lightColor * (0.33 + dirColor * 0.33 + pointColor * 0.33), 1);
	normal = vec4(abs(Normal.x), abs(Normal.y), abs(Normal.z), 1);
}
