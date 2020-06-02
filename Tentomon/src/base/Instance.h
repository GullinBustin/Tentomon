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

class Instance
{
public:
	Instance(Mesh* m, Shader shad);
	Instance();
	~Instance();

	void setTexture(Texture* text);
	void removeTexture();

	void translate(glm::vec3 translate);
	void setPosition(glm::vec3 pos);
	void setScale(glm::vec3 scale);
	void setRotation(glm::vec3 euler_angles);
	void setRotation(glm::vec3 r_direction, float r_angle);
	void setBaseModel();
	void resetBaseModel();

	void draw();

	glm::mat4 getModelMatrix();

	Mesh* mesh;
	Texture* texture = NULL;
	Shader shader;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::quat rotation = glm::quat(0,0,0,0);
	glm::mat4 base_model_matrix = glm::mat4(1);
};

