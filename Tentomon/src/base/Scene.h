#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.h"

class Scene
{
public:
	virtual void setup() = 0;
	virtual void draw(double currentTime) = 0;

	Camera camera;
};

