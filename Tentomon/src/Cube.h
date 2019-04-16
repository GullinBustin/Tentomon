#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/Mesh.h"

class Cube: public Mesh
{
public:
	Cube();
	~Cube();
	void draw();
};

