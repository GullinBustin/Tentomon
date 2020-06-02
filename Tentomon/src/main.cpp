// vidualstudio_vcpkg.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Cube.h"
#include "Plane.h"

#include "base/Config.h"
#include "base/Shader.h"
#include "base/Camera.h"
#include "base/Texture.h"
#include "base/Instance.h"
#include "base/Scene.h"

#include "DebugScene.h"

#include "demo/MyScene.h"
#include "demo/SBScene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Camera *my_camera, double deltaTime);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	int mode_debug = 0;

	GLFWwindow* window = Config::configureOpenGL(SCR_WIDTH, SCR_HEIGHT);

	if (window == NULL)
	{
		return -1;
	}

	GLuint FramebufferName = 0;
	DebugScene my_deb;
	if (mode_debug != 0) {
		Shader plane_shader = Shader("data/shaders/Passthrough.vert", "data/shaders/SimpleTexture.frag");
		Shader depth_shader = Shader("data/shaders/Passthrough.vert", "data/shaders/SimpleDepth.frag");
		my_deb = DebugScene(plane_shader, depth_shader);
		my_deb.setup(SCR_WIDTH, SCR_HEIGHT);
		FramebufferName = my_deb.FramebufferName;
	}

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	double oldCurrentTime = glfwGetTime();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	Scene* my_scene = new MyScene();
	my_scene->setup();

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Render on the whole framebuffer, complete from the lower left corner to the upper right
		my_scene->draw(glfwGetTime());

		if (mode_debug != 0) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			my_deb.draw(SCR_WIDTH, SCR_HEIGHT);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Measure speed
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - oldCurrentTime;
		oldCurrentTime = currentTime;
		nbFrames++;
		if (currentTime - lastTime >= 3.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%.2f fps\n", nbFrames/3.f);
			nbFrames = 0;
			lastTime += 3.0;
		}

		// input
		// -----
		processInput(window, &my_scene->camera, deltaTime);

	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Camera *my_camera, double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, SCR_WIDTH/2, SCR_HEIGHT/2);
	
	xpos -= SCR_WIDTH / 2;
	ypos -= SCR_HEIGHT / 2;
	my_camera->oldRotate(-xpos, -ypos);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		my_camera->oldTranslate(0, deltaTime);
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		my_camera->oldTranslate(0, -deltaTime);
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		my_camera->oldTranslate(deltaTime, 0);
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		my_camera->oldTranslate(-deltaTime, 0);
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		my_camera->changeDirection(1, 0, 0);
		my_camera->changeUp(0, 1, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		my_camera->changeDirection(-1, 0, 0);
		my_camera->changeUp(0, 1, 0);
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		my_camera->changeDirection(0, 1, 0);
		my_camera->changeUp(0, 0, 1);
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		my_camera->changeDirection(0, -1, 0);
		my_camera->changeUp(0, 0, 1);
	}

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		my_camera->changeDirection(0, 0, 1);
		my_camera->changeUp(0, 1, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		my_camera->changeDirection(0, 0, -1);
		my_camera->changeUp(0, 1, 0);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
