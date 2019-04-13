#include "camera.h"

camera::camera(float x, float y, float z,
	float vx, float vy, float vz,
	float upx, float upy, float upz, 
	float lSpeed, float aSpeed)
{
	positionX = x;
	positionY = y;
	positionZ = z;
	dirX = vx;
	dirY = vy;
	dirZ = vz;
	upX = upx;
	upY = upy;
	upZ = upz;
	linealSpeed = lSpeed;
	angularSpeed = aSpeed;

	Dir = glm::vec3(vx, vy, vz);
	Position = glm::vec3(x, y, z);
	Up = glm::vec3(upx, upy, upz);

	firstUp = Up;

}

void camera::rotateCamera(float x, float y) {
	
	glm::vec3 dirRotX = firstUp;
	glm::vec3 dirRotY = glm::cross(Dir, Up);

	glm::vec3 tempVecX = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(x*angularSpeed), dirRotX) * glm::vec4(Dir, 0));
	Dir = glm::normalize(tempVecX);

	glm::vec3 tempVecY = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(y*angularSpeed), dirRotY) * glm::vec4(Dir, 0));
	glm::vec3 tempUp = glm::cross(glm::cross(tempVecY, firstUp), tempVecY);
	
	float angl2 = glm::orientedAngle(firstUp, tempVecY, dirRotY);
	float angl1 = glm::orientedAngle(firstUp, Dir, dirRotY);

	if (angl2*angl1 >= 0.0f) {
		Up = glm::normalize(tempUp);
		Dir = glm::normalize(tempVecY);
	}
	else {
		Up = glm::normalize(glm::cross(glm::cross(Dir, firstUp), Dir));
	}

}

void camera::translateCamera(float x, float y) {

	glm::vec3 dirTransX = glm::cross(Dir, Up);
	glm::vec3 dirTransY = Dir;

	glm::vec4 tempVec = glm::translate(glm::mat4(1), dirTransX * x*linealSpeed) * glm::vec4(Position, 1.0f);
	Position = glm::vec3(tempVec);

	tempVec = glm::translate(glm::mat4(1), dirTransY * y*linealSpeed) * glm::vec4(Position, 1.0f);
	Position = glm::vec3(tempVec);

}

glm::vec3 camera::getPos() {
	return Position;
}

glm::vec3 camera::getDir() {
	return Dir;
}

glm::vec3 camera::getUp() {
	return Up;
}

camera::~camera()
{
}
