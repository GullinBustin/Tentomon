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
	Shader cubemap_shader = Shader("data/shaders/cubeMap.vert", "data/shaders/cubeMap.frag");
	Mesh* my_cube =  &Cube::getInstance();
	Mesh* floor = &Plane::getInstance();

	Scene::camera = Camera(0, 0, 3, 0, 0, -1, 0, 1, 0); //TODO: Reference to Scene Camere, not MyScene Camera. Fix it.
	Scene::camera.setProjection(); 

	Texture* t_floor = new Texture();
	t_floor->loadTexture2D("data/images/tochos.jpg");

	Texture* t_window = new Texture();
	t_window->loadTexture2D("data/images/window.png", GL_RGBA);
	
	Texture* t_cubemap = new Texture(GL_TEXTURE_CUBE_MAP);
	vector<std::string> faces
	{
		"data/images/skybox/right.jpg",
		"data/images/skybox/left.jpg",
		"data/images/skybox/top.jpg",
		"data/images/skybox/bottom.jpg",
		"data/images/skybox/front.jpg",
		"data/images/skybox/back.jpg"
	};
	t_cubemap->loadCubeMap(faces);

	Instance planeInstance = Instance(floor, floor_shader);
	planeInstance.setScale(glm::vec3(5, 5, 5));
	planeInstance.setRotation(glm::vec3(glm::radians(-90.), 0, 0));
	planeInstance.setBaseModel();
	planeInstance.setPosition(glm::vec3(0, -1, 0));
	planeInstance.setTexture(t_floor);

	Instance windowInstance = Instance(floor, floor_shader);
	windowInstance.setPosition(glm::vec3(0, 2, 1));
	windowInstance.setTexture(t_window);

	Instance cubeMapInstance = Instance(my_cube, cubemap_shader);
	cubeMapInstance.setTexture(t_cubemap);

	MyScene::cubeMapInstance = cubeMapInstance;

	const int n_cubes = 1000;
	const int x_cubes = 32;
	
	MyScene::instanceList = new Instance[2 + n_cubes]{ planeInstance };
	
	for (int i = 0; i < n_cubes; i++) {
		float x = i % x_cubes;
		float y = i / x_cubes;
		Instance cubeInstance = Instance(my_cube, my_shader);
		cubeInstance.setPosition(glm::vec3(x * 4 - (x_cubes * 4. / 2), y * 3, -1));
		MyScene::instanceList[i + 1] = cubeInstance;
	}
	MyScene::instanceList[1 + n_cubes] = windowInstance;
	

	MyScene::numOfInstances = 2 + n_cubes;
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

	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	cubeMapInstance.useShader();
	setUniforms(cubeMapInstance.shader);
	cubeMapInstance.draw();
	cubeMapInstance.stopShader();
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);

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
