#pragma once

#include "../base/Scene.h"
#include "../Cube.h"
#include "../Plane.h"
#include "../base/Instance.h"
#include "../base/UBO.h"
#include "../base/ObjectMesh.h"

class MyScene : public Scene
{
public:
	MyScene();
	~MyScene();
	void setup();
	void setUniforms();
	void draw(double currentTime);

	vector<Instance> instanceList;
	int numOfInstances;
	Instance cubeMapInstance;
	UBO my_ubo;

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 dirLight = glm::vec3(1.0f, 0.0f, -1.0f);
	glm::vec3 pointLight = glm::vec3(0.0f, 10.0f, 10.0f);
};

