#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include "Shader.h"

class Camera
{
public:
	Camera(float x, float y, float z, float vx, float vy, float vz, float upx, float upy, float upz);
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	~Camera();

	void setProjection();

	void fixPointTransate(float x, float y, float z, float px, float py, float pz);
	void pureTranslate(float x, float y, float z);

	void changeCenterPoint(float px, float py, float pz);
	void changeDirection(float vx, float vy, float vz);

	void changeUp(float upx, float upy, float upz);

	void rotateAxis(glm::vec3 axis, float angle);

	void oldTranslate(float x, float y, float linealSpeed=1.0f);
	void oldRotate(float x, float y, float angularSpeed = 0.1f);

	void setUniforms(Shader shader);

	glm::mat4 getCameraMatrix();

	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 up;

	glm::mat4 projection;

};

