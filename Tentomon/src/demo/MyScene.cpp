#include "MyScene.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

MyScene::MyScene() {

}

MyScene::~MyScene()
{
}

void MyScene::setup()
{
	Shader instance_shader = Shader("data/shaders/instanceShader.vert", "data/shaders/instanceShader.frag");
	Shader my_shader = Shader("data/shaders/vertexShader.vert", "data/shaders/fragmentShader.frag");
	//Shader color_shader = Shader("data/shaders/objColorShader.vert", "data/shaders/objColorShader.frag");
	Shader floor_shader = Shader("data/shaders/vertexShader.vert", "data/shaders/SimpleTexture.frag");
	Shader cubemap_shader = Shader("data/shaders/cubeMap.vert", "data/shaders/cubeMap.frag");
	Shader obj_shader = Shader("data/shaders/objShader.vert", "data/shaders/objShader.frag");
	Mesh* my_cube =  &Cube::getInstance();
	Mesh* floor = &Plane::getInstance();

	my_shader.setUniformBlock("Camera", 0);
	cubemap_shader.setUniformBlock("Camera", 0);
	instance_shader.setUniformBlock("Camera", 0);

	my_shader.setUniformBlock("Light", 1);

	Scene::camera = Camera(0, 1, 10, 0, 0, -1, 0, 1, 0); //TODO: Reference to Scene Camere, not MyScene Camera. Fix it.
	Scene::camera.setProjection(); 

	Assimp::Importer importer;
	const aiScene* tentomon_scene = importer.ReadFile("data/models/Tentomon.obj", aiProcess_Triangulate | aiProcess_GenNormals);
	Mesh* my_tentomon = new ObjectMesh(tentomon_scene, 0);
	Texture* t_tentomon = new Texture();
	t_tentomon->loadTexture2D("data/models/Tentomon.png");

	const aiScene* trol_scene = importer.ReadFile("data/models/trol.glb", aiProcess_Triangulate | aiProcess_GenNormals);
	Mesh* my_trol = new ObjectMesh(trol_scene, 0);
	Texture* t_trol = new Texture();
	aiMaterial* my_material = trol_scene->mMaterials[0];
	aiString str;
	my_material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
	const aiTexture* trol_texture = trol_scene->GetEmbeddedTexture(str.C_Str());
	t_trol->createTextureFromAiTexture(trol_texture);

	Texture* t_floor = new Texture();
	t_floor->loadTexture2D("data/images/tochos.jpg");

	Texture* t_window = new Texture();
	t_window->loadTexture2D("data/images/window.png");

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

	Instance trolInstance = Instance(my_trol, obj_shader);
	trolInstance.setPosition(glm::vec3(-2, 0, 0));
	trolInstance.setTexture(t_trol);
	//MyScene::instanceList.push_back(trolInstance);

	Instance tentomonInstance = Instance(my_tentomon, obj_shader);
	tentomonInstance.setTexture(t_tentomon);
	//MyScene::instanceList.push_back(tentomonInstance);

	Instance planeInstance = Instance(floor, floor_shader);
	planeInstance.setScale(glm::vec3(5, 5, 5));
	planeInstance.setRotation(glm::vec3(glm::radians(-90.), 0, 0));
	planeInstance.setBaseModel();
	planeInstance.setPosition(glm::vec3(0, 0, 0));
	planeInstance.setTexture(t_floor);

	Instance windowInstance = Instance(floor, floor_shader);
	windowInstance.setPosition(glm::vec3(-2, 2, 3));
	windowInstance.setTexture(t_window);

	Instance cubeMapInstance = Instance(my_cube, cubemap_shader);
	cubeMapInstance.setTexture(t_cubemap);

	MyScene::cubeMapInstance = cubeMapInstance;

	const int n_cubes = 10000;
	const int x_cubes = 100;

	//Instance cubeInstance = Instance(my_cube, my_shader);
	//cubeInstance.setPosition(glm::vec3(0,0,0));
	/*
	for (int i = 0; i < n_cubes; i++) {
		float x = i % x_cubes;
		float y = i / x_cubes;
		Instance cubeInstance = Instance(my_cube, my_shader);
		cubeInstance.setPosition(glm::vec3(x * 4 - (x_cubes * 4. / 2), y * 3, -1));
		MyScene::instanceList.push_back(cubeInstance);
	}*/
	
	MyScene::instanceList.push_back(planeInstance);
	//MyScene::instanceList.push_back(windowInstance);
	
	multi = MultiInstance(my_cube, instance_shader, n_cubes);

	for (int i = 0; i < n_cubes; i++) {
		float x = i % x_cubes;
		float y = i / x_cubes;
		multi.setPosition(glm::vec3(x * 4 - (x_cubes * 4. / 2), y * 3 -(x_cubes * 4. / 2), -1), i);
	}
	multi.calculateModels();

	my_ubo = UBO();
	my_ubo.addUniform("view", 0, sizeof(glm::mat4));
	my_ubo.addUniform("projection", 0, sizeof(glm::mat4));
	my_ubo.addUniform("lightColor", 1, sizeof(glm::vec3));
	my_ubo.addUniform("dirLight", 1, sizeof(glm::vec3));
	my_ubo.addUniform("pointLight", 1, sizeof(glm::vec3));
	my_ubo.createUBO();
}

void MyScene::setUniforms()
{
	my_ubo.setUniform("view", 0, glm::value_ptr(camera.getCameraMatrix()));
	my_ubo.setUniform("projection", 0, glm::value_ptr(camera.projection));
	my_ubo.setUniform("lightColor", 1, glm::value_ptr(lightColor));
	my_ubo.setUniform("dirLight", 1, glm::value_ptr(dirLight));
	my_ubo.setUniform("pointLight", 1, glm::value_ptr(pointLight));
}

void MyScene::draw(double currentTime)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setUniforms();

	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	cubeMapInstance.useShader();
	cubeMapInstance.draw();
	cubeMapInstance.stopShader();
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);

	multi.useShader();
	multi.draw();
	multi.stopShader();

	Shader current_shader = instanceList[0].shader;
	current_shader.useShader();
	for (int i = 0; i < instanceList.size(); i++) {
		if (current_shader != instanceList[i].shader) {
			current_shader.stopShader();
			current_shader = instanceList[i].shader;
			current_shader.useShader();
		}
		instanceList[i].draw();
	}
	current_shader.stopShader();
}
