#include "MultiInstance.h"

MultiInstance::MultiInstance(Mesh* m, Shader shad, int n) : mesh(m), shader(shad)
{
	position = vector<glm::vec3>(n, glm::vec3(0, 0, 0));
	scale = vector<glm::vec3>(n, glm::vec3(1, 1, 1));
	rotation = vector<glm::quat>(n, glm::quat(0, 0, 0, 0));
	model = vector<glm::mat4>(n, glm::mat4(1));

	unsigned int VAO = m->VAO;
	glBindVertexArray(VAO);

	glGenBuffers(1, &modelBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
	glBufferData(GL_ARRAY_BUFFER, n * sizeof(glm::mat4), &model[0], GL_STATIC_DRAW);

	// set attribute pointers for matrix (4 times vec4)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);

}

MultiInstance::MultiInstance()
{
}

MultiInstance::~MultiInstance()
{
}

void MultiInstance::setTexture(Texture* text)
{
	texture = text;
}

void MultiInstance::removeTexture()
{
	texture = NULL;
}

void MultiInstance::translate(glm::vec3 translate, int n)
{
	if (position.size() > n) {
		position[n] += translate;
	}
	else {
		std::cerr << "Position n is higher than vector size" << std::endl;
		throw;
	}
}

void MultiInstance::setPosition(glm::vec3 pos, int n)
{
	if (n > -1) {
		position[n] = pos;
	}
	else {
		globalPosition = pos;
		base_model_matrix = getModelMatrix(-1);
	}
}

void MultiInstance::setScale(glm::vec3 scale, int n)
{
	if (n > -1) {
		MultiInstance::scale[n] = scale;
	}
	else {
		globalScale = scale;
		base_model_matrix = getModelMatrix(-1);
	}
}

void MultiInstance::setRotation(glm::vec3 euler_angles, int n)
{
	if (n > -1) {
		MultiInstance::rotation[n] = glm::quat(euler_angles);
	}
	else {
		globalRotation = glm::quat(euler_angles);
		base_model_matrix = getModelMatrix(-1);
	}
}

void MultiInstance::setRotation(glm::vec3 r_direction, float r_angle, int n)
{
	
	if (n > -1) {
		MultiInstance::rotation[n] = glm::angleAxis(r_angle, r_direction);;
	}
	else {
		globalRotation = glm::angleAxis(r_angle, r_direction);
		base_model_matrix = getModelMatrix(-1);
	}
}

void MultiInstance::calculateModels() {
	for (int i = 0; i < model.size(); i++) {
		model[i] = getModelMatrix(i);
	}
}

void MultiInstance::draw()
{
	
	glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
	glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(glm::mat4), &model[0], GL_STATIC_DRAW);
	
	if (texture != NULL) {
		shader.setUniform("renderedTexture", 0);
		texture->useTexture();
	}
	mesh->drawInstances(model.size());

	if (texture != NULL) texture->stopTexture();
}

void MultiInstance::useShader() {
	shader.useShader();
}

void MultiInstance::stopShader() {
	shader.stopShader();
}

glm::mat4 MultiInstance::getModelMatrix(int n)
{
	if (n > -1) {
		glm::mat4 model = glm::translate(position[n]);
		model = model * glm::toMat4(rotation[n]);
		model = glm::scale(model, scale[n]);
		return model * base_model_matrix;
	}
	else {
		glm::mat4 model = glm::translate(globalPosition);
		model = model * glm::toMat4(globalRotation);
		model = glm::scale(model, globalScale);
		return model;
	}
}
