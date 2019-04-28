#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Instance.h"

class Scene
{
public:
	Scene();
	~Scene();

	void setCamera(Camera* cam);
	void setInstances(Instance* instList, int numInst);

	void draw();

	void setUniforms(Shader shader);

	GLuint framebuffer = 0;

	Instance* instanceList;
	int numOfInstances;

	Camera* camera;

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 dirLight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 pointLight = glm::vec3(0.0f, 2.0f, -2.0f);
};

