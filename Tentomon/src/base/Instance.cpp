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
	position = pos;
}

void Instance::lookAt(glm::vec3 point, float upAngle)
{
	direction = point - position;
	upRotation = upAngle;
}

void Instance::draw()
{
	shader.useShader();
	shader.setUniform("M", getModelMatrix());

	if (texture != NULL) {
		shader.setUniform("renderedTexture", 0);
		texture->useTexture();
	}
	mesh->draw();
	if (texture != NULL) texture->stopTexture();

	shader.stopShader();
}

glm::mat4 Instance::getModelMatrix()
{
	glm::vec3 up = glm::rotate(glm::vec3(0, 1, 0), upRotation, direction);
	return glm::lookAt(
		position,
		position + direction,
		up
	);
}
