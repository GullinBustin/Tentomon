#include <glm/glm.hpp>
#include "SBScene.h"
#include "../Plane.h"

SBScene::SBScene()
{
}

SBScene::~SBScene()
{
}

void SBScene::setup()
{
	Shader shader = Shader("data/shaders/SBShaders/vertex.vert",
		"data/shaders/SBShaders/fragment.frag");
	Mesh* plane = &Plane::getInstance();

	Scene::camera = Camera(0, 0, 3, 0, 0, -1, 0, 1, 0); //TODO: Reference to Scene Camere, not MyScene Camera. Fix it.
	Scene::camera.setProjection();

	planeInstance = Instance(plane, shader);
	planeInstance.setPosition(glm::vec3(1, 1, -2));
}

void SBScene::draw(double currentTime)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	planeInstance.setPosition(glm::vec3(0, 0, 0));
	camera.setUniforms(planeInstance.shader);
	planeInstance.draw();
}
