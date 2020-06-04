#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path,
	const char* tessellation_control_file_path = NULL, const char* tessellation_evaluation_file_path = NULL,
	const char* geometry_file_path = NULL);

class Shader
{
public:
	GLuint programID;
	Shader();
	Shader(const char* vertex_file_path, const char* fragment_file_path,
		const char* tessellation_control_file_path = NULL, const char* tessellation_evaluation_file_path = NULL,
		const char* geometry_file_path = NULL);
	~Shader();
	map<const GLchar*, GLuint> uniformIds;
	void setUniform(const GLchar* name, int);
	void setUniform(const GLchar* name, float);
	void setUniform(const GLchar* name, glm::vec2);
	void setUniform(const GLchar *name, glm::vec3);
	void setUniform(const GLchar *name, glm::mat4, GLboolean transpose = 0);
	void useShader();
	void stopShader();

	bool operator==(const Shader& b);
	bool operator!=(const Shader& b);
};

