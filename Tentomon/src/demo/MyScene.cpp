#include "MyScene.h"
#include <glm/glm.hpp>

MyScene::MyScene() {

}

MyScene::~MyScene()
{
}

void MyScene::setup()
{
	Shader my_shader = Shader("data/shaders/vertexShader.vert", "data/shaders/fragmentShader.frag");
	Mesh* my_cube =  &Cube::getInstance();
	Scene::camera = Camera(0, 0, 3, 0, 0, -1, 0, 1, 0); //TODO: Reference to Scene Camere, not MyScene Camera. Fix it.
	Scene::camera.setProjection(); 

	my_shader.useShader();
	my_shader.setUniform("lightColor", lightColor);
	my_shader.setUniform("dirLight", dirLight);
	my_shader.setUniform("pointLight", pointLight);
	my_shader.stopShader();

	Instance cubeInstance = Instance(my_cube, my_shader);
	/*Instance cubeInstance2 = Instance(my_cube, my_shader);
	Instance cubeInstance3 = Instance(my_cube, my_shader);
	Instance cubeInstance4 = Instance(my_cube, my_shader);
	cubeInstance2.setPosition(glm::vec3(10, 0, 0));
	cubeInstance3.setPosition(glm::vec3(-10, 0, 0));
	cubeInstance4.setPosition(glm::vec3(0, 10, 0));*/

	MyScene::instanceList = new Instance[1] { cubeInstance};
	MyScene::numOfInstances = 1;

}

void MyScene::setUniforms(Shader shader)
{
	shader.useShader();
	shader.setUniform("lightColor", lightColor);
	shader.setUniform("dirLight", dirLight);
	shader.setUniform("pointLight", pointLight);
	shader.stopShader();
}

void MyScene::draw(double currentTime)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < numOfInstances; i++) {
		setUniforms(instanceList[i].shader);
		camera.setUniforms(instanceList[i].shader);
		instanceList[i].draw();
	}
}