#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/Shader.h"
#include "base/Texture.h"
#include "base/Mesh.h"
#include "Plane.h"


class DebugScene
{
public:
	DebugScene();
	DebugScene(Shader &text, Shader &depth) : texture_shad(text), depth_shad(depth) {};
	~DebugScene() {};
	void setup(unsigned int w, unsigned int h);
	void draw(int w, int h);

	Shader texture_shad;
	Shader depth_shad;

	GLuint FramebufferName;

	Texture scene_texture;
	Texture normal_texture; 
	Texture depth_texture;

	Mesh* plane;
};

inline DebugScene::DebugScene()
{
}

void DebugScene::setup(unsigned int w, unsigned int h) {
	///RENDER TEXTURE///
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	scene_texture = Texture();
	scene_texture.emptyTexture(w, h);

	normal_texture = Texture();
	normal_texture.emptyTexture(w, h);

	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	depth_texture = Texture();
	glBindTexture(GL_TEXTURE_2D, depth_texture.textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, scene_texture.textureID, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, normal_texture.textureID, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture.textureID, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, DrawBuffers); // "1" is the size of DrawBuffers

	plane = &Plane::getInstance();
}

void DebugScene::draw(int w, int h)
{

	glViewport(0, 0, w / 2, h / 2);
	texture_shad.useShader();
	scene_texture.useTexture();
	texture_shad.setUniform("renderedTexture", 0);
	plane->draw();
	scene_texture.stopTexture();

	glViewport(0, h / 2, w / 2, h / 2);
	normal_texture.useTexture();
	plane->draw();
	normal_texture.stopTexture();
	texture_shad.stopShader();

	glViewport(w / 2, h / 2, w / 2, h / 2);
	depth_shad.useShader();
	depth_shad.setUniform("renderedTexture", 0);
	depth_texture.useTexture();
	plane->draw();
	depth_texture.stopTexture();
	depth_shad.stopShader();
	
};