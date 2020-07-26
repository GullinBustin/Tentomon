#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Shader.h"

class Mesh
{
public:
	virtual void draw();
	virtual void drawInstances(int n);
	unsigned int VAO;

protected:
	Mesh();
	~Mesh();

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int VBO, EBO;
};

