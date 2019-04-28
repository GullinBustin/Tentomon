#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::setCamera(Camera* cam)
{
	camera = cam;
}

void Scene::setInstances(Instance* instList, int numInst)
{
	instanceList = instList;
	numOfInstances = numInst;
}

void Scene::draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < numOfInstances; i++) {
		setUniforms(instanceList[i].shader);
		camera->setUniforms(instanceList[i].shader);
		instanceList[i].draw();
	}
}

void Scene::setUniforms(Shader shader)
{
	shader.useShader();
	shader.setUniform("lightColor", lightColor);
	shader.setUniform("dirLight", dirLight);
	shader.setUniform("pointLight", pointLight);
	shader.stopShader();
}