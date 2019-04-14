#include "Camera1.h"



Camera1::Camera1(float x, float y, float z, float vx, float vy, float vz, float upx, float upy, float upz)
{
	direction = glm::vec3(vx, vy, vz);
	position = glm::vec3(x, y, z);
	up = glm::vec3(upx, upy, upz);
}

Camera1::Camera1(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
	direction = dir;
	position = pos;
	Camera1::up = up;
}

Camera1::~Camera1()
{
}

void Camera1::fixPointTransate(float x, float y, float z, float px, float py, float pz)
{
	position += glm::vec3(x, y, z);
	direction = glm::vec3(px, py, pz) - position;
}

void Camera1::pureTranslate(float x, float y, float z)
{
	position += glm::vec3(x, y, z);
}

void Camera1::changeCenterPoint(float px, float py, float pz)
{
	direction = glm::vec3(px, py, pz) - position;
}

void Camera1::changeDirection(float vx, float vy, float vz)
{
	direction = glm::vec3(vx, vy, vz);
}

void Camera1::changeUp(float upx, float upy, float upz)
{
	up = glm::vec3(upx, upy, upz);
}

void Camera1::rotateAxis(glm::vec3 axis, float angle)
{
	direction = glm::rotate(direction, angle, axis);
}

glm::mat4 Camera1::getCameraMatrix()
{
	glm::mat4 viewMatrix = glm::lookAt(
		position, // Camera is at (4,3,3), in World Space
		position + direction, // and looks at the origin
		up  // Head is up (set to 0,-1,0 to look upside-down)
	);
	return viewMatrix;
}
