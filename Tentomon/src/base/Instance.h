#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp> 

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

	void lookAt(glm::vec3 point, float upAngle = 0);

	void draw();

	glm::mat4 getModelMatrix();

	Mesh* mesh;
	Texture* texture = NULL;
	Shader shader;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 direction = glm::vec3(0, 0, 1);
	float upRotation = 0;
};

