#pragma once

#include "../base/Scene.h"
#include "../Cube.h"
#include "../base/Instance.h"

class MyScene : public Scene
{
public:
	MyScene();
	~MyScene();
	void setup();
	void setUniforms(Shader shader);
	void draw(double currentTime);

	Instance* instanceList;
	int numOfInstances;

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 dirLight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 pointLight = glm::vec3(0.0f, 2.0f, -2.0f);

};

