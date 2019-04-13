#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <iostream>

class camera
{
public:
	camera(float x, float y, float z, float vx, float vy, float vz, float upx, float upy, float upz, float lSpeed, float aSpeed);
	~camera();
	void rotateCamera(float x, float y);

	void translateCamera(float x, float y);

	glm::vec3 getPos();

	glm::vec3 getDir();

	glm::vec3 getUp();

private:
	float positionX, positionY, positionZ;
	float dirX, dirY, dirZ;
	float upX, upY, upZ;
	float linealSpeed, angularSpeed;
	glm::vec3 Dir;
	glm::vec3 Position;
	glm::vec3 Up;
	glm::vec3 firstUp;
};

