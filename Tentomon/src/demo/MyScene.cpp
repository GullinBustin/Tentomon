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
	Shader floor_shader = Shader("data/shaders/vertexShader.vert", "data/shaders/SimpleTexture.frag");
	Mesh* my_cube =  &Cube::getInstance();
	Mesh* floor = &Plane::getInstance();

	Scene::camera = Camera(0, 0, 3, 0, 0, -1, 0, 1, 0); //TODO: Reference to Scene Camere, not MyScene Camera. Fix it.
	Scene::camera.setProjection(); 

	Texture t_floor = Texture();
	t_floor.getFromFile("data/images/tochos.jpg");

	Instance cubeInstance = Instance(my_cube, my_shader);
	/*Instance cubeInstance2 = Instance(my_cube, my_shader);
	Instance cubeInstance3 = Instance(my_cube, my_shader);
	Instance cubeInstance4 = Instance(my_cube, my_shader);
	cubeInstance2.setPosition(glm::vec3(10, 0, 0));
	cubeInstance3.setPosition(glm::vec3(-10, 0, 0));
	cubeInstance4.setPosition(glm::vec3(0, 10, 0));*/
	Instance planeInstance = Instance(floor, floor_shader);
	planeInstance.setScale(glm::vec3(2, 2, 2));
	planeInstance.setRotation(glm::vec3(glm::radians(-90.), 0, 0));
	planeInstance.setBaseModel();
	planeInstance.setPosition(glm::vec3(0, -1, 0));
	planeInstance.setTexture(&t_floor);
	// cubeInstance
	MyScene::instanceList = new Instance[2] { planeInstance, cubeInstance };
	MyScene::numOfInstances = 2;

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
