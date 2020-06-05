#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>


class Texture
{
public:
	Texture(int texture_type = GL_TEXTURE_2D);
	~Texture();
	void emptyTexture(int width, int height);
	void loadTexture2D(char const* filename, int image_format = GL_RGB);
	void loadCubeMap(std::vector<std::string> faces, int image_format = GL_RGB);
	void useTexture(unsigned int textureNumber = GL_TEXTURE0);
	void stopTexture();

	GLuint textureID;
	int texture_type;

private:

	void create_2d_t();
	void create_cube_map_t();
};

