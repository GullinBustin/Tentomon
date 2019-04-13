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

#include <glad/glad.h>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

class Shader
{
public:
	Shader();
	~Shader();
};

