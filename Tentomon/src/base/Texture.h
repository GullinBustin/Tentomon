#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <assimp/scene.h>


class Texture
{
public:
	Texture(int texture_type = GL_TEXTURE_2D);
	~Texture();
	void emptyTexture(int width, int height);
	void createTextureFromAiTexture(const aiTexture* texture);
	void loadTexture2D(char const* filename);
	void loadCubeMap(std::vector<std::string> faces, int image_format = GL_RGB);
	void useTexture(unsigned int textureNumber = GL_TEXTURE0);
	void stopTexture();

	GLuint textureID;
	int texture_type;
	
private:

	void create_2d_t();
	void create_cube_map_t();
};

