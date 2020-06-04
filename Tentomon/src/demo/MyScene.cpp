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

	Texture *t_floor = new Texture();
	t_floor->getFromFile("data/images/tochos.jpg");

	Instance planeInstance = Instance(floor, floor_shader);
	planeInstance.setScale(glm::vec3(5, 5, 5));
	planeInstance.setRotation(glm::vec3(glm::radians(-90.), 0, 0));
	planeInstance.setBaseModel();
	planeInstance.setPosition(glm::vec3(0, -1, 0));
	planeInstance.setTexture(t_floor);

	const int n_cubes = 1000;
	const int x_cubes = 32;
	MyScene::instanceList = new Instance[1 + n_cubes]{ planeInstance };
	//MyScene::instanceList = new Instance[n_cubes]{ planeInstance };

	for (int i = 0; i < n_cubes; i++) {
		float x = i % x_cubes;
		float y = i / x_cubes;
		Instance cubeInstance = Instance(my_cube, my_shader);
		cubeInstance.setPosition(glm::vec3(x * 4 - (x_cubes * 4. / 2), y * 3, 0));
		MyScene::instanceList[i + 1] = cubeInstance;
		//MyScene::instanceList[i] = cubeInstance;
	}
	
	MyScene::numOfInstances = 1 + n_cubes;
	//MyScene::numOfInstances = n_cubes;
}

void MyScene::setUniforms(Shader shader)
{
	shader.setUniform("lightColor", lightColor);
	shader.setUniform("dirLight", dirLight);
	shader.setUniform("pointLight", pointLight);
	camera.setUniforms(shader);
}

void MyScene::draw(double currentTime)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader current_shader = instanceList[0].shader;
	current_shader.useShader();
	setUniforms(current_shader);
	for (int i = 0; i < numOfInstances; i++) {
		if (current_shader != instanceList[i].shader) {
			current_shader.stopShader();
			current_shader = instanceList[i].shader;
			current_shader.useShader();
			setUniforms(current_shader);
		}
		instanceList[i].draw();
	}
	current_shader.stopShader();
}
