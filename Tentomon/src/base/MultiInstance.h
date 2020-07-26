#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Instance.h"

class MultiInstance: public Instance
{
public:
	MultiInstance(Mesh* m, Shader shad, int n);
	MultiInstance();
	~MultiInstance();

	void setTexture(Texture* text);
	void removeTexture();

	void translate(glm::vec3 translate, int n);
	void setPosition(glm::vec3 pos, int n);
	void setScale(glm::vec3 scale, int n);
	void setRotation(glm::vec3 euler_angles, int n);
	void setRotation(glm::vec3 r_direction, float r_angle, int n);

	void calculateModels();

	void draw();

	void useShader();
	void stopShader();

	glm::mat4 getModelMatrix(int n);

	Mesh* mesh;
	Texture* texture = NULL;
	Shader shader;
	unsigned int modelBuffer;

	vector<glm::vec3> position;
	vector<glm::vec3> scale;
	vector<glm::quat> rotation;
	vector<glm::mat4> model;
	glm::vec3 globalPosition = glm::vec3(0, 0, 0);
	glm::vec3 globalScale = glm::vec3(1, 1, 1);
	glm::quat globalRotation = glm::quat(0, 0, 0, 0);
    glm::mat4 base_model_matrix = glm::mat4(1);
};

