#include "Instance.h"

Instance::Instance(Mesh* m, Shader shad) : mesh(m), shader(shad)
{
}

Instance::Instance()
{
}

Instance::~Instance()
{
}

void Instance::setTexture(Texture* text)
{
	texture = text;
}

void Instance::removeTexture()
{
	texture = NULL;
}

void Instance::translate(glm::vec3 translate)
{
	position += translate;
}

void Instance::setPosition(glm::vec3 pos)
{
	Instance::position = pos;
}

void Instance::setScale(glm::vec3 scale)
{
	Instance::scale = scale;
}

void Instance::setRotation(glm::vec3 euler_angles)
{
	rotation = glm::quat(euler_angles);
}

void Instance::setRotation(glm::vec3 r_direction, float r_angle)
{
	rotation = glm::angleAxis(r_angle, r_direction);
}

void Instance::setBaseModel()
{
	base_model_matrix = getModelMatrix();
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	rotation = glm::quat(0, 0, 0, 0);
}

void Instance::resetBaseModel()
{
	base_model_matrix = glm::mat4(1);
}

void Instance::draw()
{
	shader.setUniform("M", getModelMatrix());

	if (texture != NULL) {
		shader.setUniform("renderedTexture", 0);
		texture->useTexture();
	}
	mesh->draw();
	if (texture != NULL) texture->stopTexture();
}

void Instance::useShader() {
	shader.useShader();
}

void Instance::stopShader() {
	shader.stopShader();
}

glm::mat4 Instance::getModelMatrix()
{
	glm::mat4 model = glm::translate(position);
	model = model * glm::toMat4(rotation);
	model = glm::scale(model, Instance::scale);
	return model * base_model_matrix;
}
