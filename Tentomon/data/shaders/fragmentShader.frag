#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 lightColor;
uniform vec3 dirLight;
uniform vec3 cameraPos;
uniform vec3 pointLight;

void main()
{
	float specularMaterial = 1.0f;
	float specularPow = 32;

	vec3 pointLightDir = normalize(Position - pointLight);
	vec3 viewDir = normalize(Position - cameraPos);

	float dirLightDiffuse = max(dot(Normal,dirLight), 0);
	vec3 dirReflectDir = reflect(dirLight, Normal);
	float dirLightSpecular = pow(max(dot(viewDir, dirReflectDir), 0.0), specularPow);
	float dirColor = dirLightDiffuse + dirLightSpecular * specularMaterial;

	float pointDiffuse = max(dot(Normal,-pointLightDir), 0);
	vec3 pointReflectDir = reflect(pointLightDir, Normal);
	float pointSpecular = pow(max(dot(viewDir, -pointReflectDir), 0.0), specularPow);
	float pointColor = pointDiffuse + pointSpecular * specularMaterial;

	FragColor = vec4(lightColor * (0.33 + dirColor * 0.33 + pointColor * 0.33), 1);
}
