#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(int texture_type)
{
	glGenTextures(1, &textureID);
	Texture::texture_type = texture_type;

	switch (texture_type)
	{
	case GL_TEXTURE_2D:
		create_2d_t();
		break;
	case GL_TEXTURE_CUBE_MAP:
		create_cube_map_t();
		break;
	}
}

void Texture::emptyTexture(int width, int height) {
	glBindTexture(texture_type, textureID);
	glTexImage2D(texture_type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBindTexture(texture_type, 0);

}

void Texture::createTextureFromAiTexture(const aiTexture* texture) {
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	glBindTexture(GL_TEXTURE_2D, textureID);
	unsigned char* data;
	if (texture->mHeight == 0) {
		data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData),
			texture->mWidth, &width, &height, &nrChannels, 0);
	}
	else {
		data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData),
			texture->mWidth * texture->mHeight, &width, &height, &nrChannels, 0);
	}
	if (nrChannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	if (nrChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture2D(char const* filename, bool flip_texture) {
	stbi_set_flip_vertically_on_load(flip_texture);

	glBindTexture(GL_TEXTURE_2D, textureID);
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadCubeMap(std::vector<std::string> faces, int image_format) {
	stbi_set_flip_vertically_on_load(false);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, image_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
}


Texture::~Texture()
{
}

void Texture::useTexture(unsigned int textureNumber)
{
	glActiveTexture(textureNumber);
	glBindTexture(texture_type, textureID);

}

void Texture::stopTexture()
{
	glBindTexture(texture_type, 0);
}

void Texture::create_2d_t()
{
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::create_cube_map_t() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
