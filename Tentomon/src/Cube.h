#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Cube
{
public:
	Cube(bool normals);
	~Cube();
	void draw();

private:
	GLuint vertexbuffer;
	GLuint elementbuffer;
	GLuint normalbuffer;
	bool withNormals;

};

