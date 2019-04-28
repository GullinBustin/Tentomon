#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/Shader.h"
#include "base/Texture.h"
#include "base/Mesh.h"


class DebugScene
{
public:
	DebugScene(Shader &text, Shader &depth) : texture_shad(text), depth_shad(depth) {};
	~DebugScene() {};
	void draw(Texture &simple, Texture &normal, Texture &depth, int w, int h, Mesh* plane);

	Shader texture_shad;
	Shader depth_shad;
};

void DebugScene::draw(Texture &simple, Texture &normal, Texture &depth, int w, int h, Mesh* plane)
{

	glViewport(0, 0, w / 2, h / 2);
	texture_shad.useShader();
	simple.useTexture();
	texture_shad.setUniform("renderedTexture", 0);
	plane->draw();
	simple.stopTexture();

	glViewport(0, h / 2, w / 2, h / 2);
	normal.useTexture();
	plane->draw();
	normal.stopTexture();
	texture_shad.stopShader();

	glViewport(w / 2, h / 2, w / 2, h / 2);
	depth_shad.useShader();
	depth_shad.setUniform("renderedTexture", 0);
	depth.useTexture();
	plane->draw();
	depth.stopTexture();
	depth_shad.stopShader();
	
};