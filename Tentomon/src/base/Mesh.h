#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Shader.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
	~Mesh();
	void draw(Shader shader);
	unsigned int VAO;

protected:

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int VBO, EBO;
};

