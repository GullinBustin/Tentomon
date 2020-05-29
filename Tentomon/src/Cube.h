#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/Mesh.h"
#include "base/Singleton.h"

class Cube: public Mesh, public Singleton<Cube>
{
public:
	friend class Singleton<Cube>;
	Cube();
	~Cube();
	void draw();
};

