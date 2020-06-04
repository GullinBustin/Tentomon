#include "Camera.h"

Camera::Camera()
{
	direction = glm::vec3(0, 0, 1);
	position = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);
}

Camera::Camera(float x, float y, float z, float vx, float vy, float vz, float upx, float upy, float upz)
{
	direction = glm::vec3(vx, vy, vz);
	position = glm::vec3(x, y, z);
	up = glm::vec3(upx, upy, upz);
}

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
	direction = dir;
	position = pos;
	Camera::up = up;
}

Camera::~Camera()
{
}

void Camera::setProjection() //TODO
{
	projection = glm::perspective(
		glm::radians(45.0f), // El campo de visión vertical, en radián: la cantidad de "zoom". Piensa en el lente de la cámara. Usualmente está entre 90° (extra ancho) y 30° (zoom aumentado)
		4.0f / 3.0f,       // Proporción. Depende del tamaño de tu ventana 4/3 == 800/600 == 1280/960, Parece familiar?
		0.01f,              // Plano de corte cercano. Tan grande como sea posible o tendrás problemas de precisión.
		100.0f             // Plano de corte lejano. Tan pequeño como se pueda.
	);
}

void Camera::fixPointTransate(float x, float y, float z, float px, float py, float pz)
{
	position += glm::vec3(x, y, z);
	direction = glm::vec3(px, py, pz) - position;
}

void Camera::pureTranslate(float x, float y, float z)
{
	position += glm::vec3(x, y, z);
}

void Camera::changeCenterPoint(float px, float py, float pz)
{
	direction = glm::vec3(px, py, pz) - position;
}

void Camera::changeDirection(float vx, float vy, float vz)
{
	direction = glm::vec3(vx, vy, vz);
}

void Camera::changeUp(float upx, float upy, float upz)
{
	up = glm::vec3(upx, upy, upz);
}

void Camera::rotateAxis(glm::vec3 axis, float angle)
{
	direction = glm::rotate(direction, angle, axis);
}

glm::mat4 Camera::getCameraMatrix()
{
	glm::mat4 viewMatrix = glm::lookAt(
		position, // Camera is at (4,3,3), in World Space
		position + direction, // and looks at the origin
		up  // Head is up (set to 0,-1,0 to look upside-down)
	);
	return viewMatrix;
}

void Camera::oldRotate(float x, float y, float angularSpeed) {

	glm::vec3 dirRotX = up;
	glm::vec3 dirRotY = glm::cross(direction, up);

	glm::vec3 tempVecX = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(x*angularSpeed), dirRotX) * glm::vec4(direction, 0));
	direction = glm::normalize(tempVecX);

	glm::vec3 tempVecY = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(y*angularSpeed), dirRotY) * glm::vec4(direction, 0));

	float angl2 = glm::orientedAngle(up, tempVecY, dirRotY);
	float angl1 = glm::orientedAngle(up, direction, dirRotY);

	if (angl2*angl1 >= 0.001f) {
		direction = glm::normalize(tempVecY);
	}

}

void Camera::setUniforms(Shader shader) //TODO
{
	shader.setUniform("V", getCameraMatrix());
	shader.setUniform("P", projection);
	shader.setUniform("cameraPos", position);
}

void Camera::oldTranslate(float x, float y, float linealSpeed) {

	glm::vec3 dirTransX = glm::cross(direction, up);
	glm::vec3 dirTransY = direction;

	glm::vec4 tempVec = glm::translate(glm::mat4(1), dirTransX * x*linealSpeed) * glm::vec4(position, 1.0f);
	position = glm::vec3(tempVec);

	tempVec = glm::translate(glm::mat4(1), dirTransY * y*linealSpeed) * glm::vec4(position, 1.0f);
	position = glm::vec3(tempVec);

}