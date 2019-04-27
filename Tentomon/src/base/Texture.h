#pragma once
#include <glad/glad.h>
#include <iostream>


class Texture
{
public:
	Texture();
	~Texture();
	void emptyTexture(int width, int height);
	void getFromFile(char const* filename);
	void useTexture(unsigned int textureNumber = GL_TEXTURE0);
	void stopTexture();

	GLuint textureID;
};

