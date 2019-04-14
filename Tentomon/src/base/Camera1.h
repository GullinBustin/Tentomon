#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <iostream>

class Camera1
{
public:
	Camera1(float x, float y, float z, float vx, float vy, float vz, float upx, float upy, float upz);
	Camera1(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	~Camera1();

	void fixPointTransate(float x, float y, float z, float px, float py, float pz);
	void pureTranslate(float x, float y, float z);

	void changeCenterPoint(float px, float py, float pz);
	void changeDirection(float vx, float vy, float vz);

	void changeUp(float upx, float upy, float upz);

	void rotateAxis(glm::vec3 axis, float angle);

	glm::mat4 getCameraMatrix();

	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 up;

};

