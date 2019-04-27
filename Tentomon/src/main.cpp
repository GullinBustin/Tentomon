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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Camera *my_camera, double deltaTime);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	GLFWwindow* window = Config::configureOpenGL(SCR_WIDTH, SCR_HEIGHT);

	if (window == NULL)
	{
		return -1;
	}

	glfwSwapInterval(1);


	glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);

	Shader my_shader = Shader("data/shaders/vertexShader.vert", "data/shaders/fragmentShader.frag");
	Shader plane_shader = Shader("data/shaders/Passthrough.vert", "data/shaders/SimpleTexture.frag");

	glm::mat4 Projection = glm::perspective(
		glm::radians(45.0f), // El campo de visión vertical, en radián: la cantidad de "zoom". Piensa en el lente de la cámara. Usualmente está entre 90° (extra ancho) y 30° (zoom aumentado)
		4.0f / 3.0f,       // Proporción. Depende del tamaño de tu ventana 4/3 == 800/600 == 1280/960, Parece familiar?
		0.01f,              // Plano de corte cercano. Tan grande como sea posible o tendrás problemas de precisión.
		100.0f             // Plano de corte lejano. Tan pequeño como se pueda.
	);

	glm::mat4 View;
	glm::mat4 Model = glm::mat4(1.f);

	Mesh* my_plane = new Plane();
	Mesh* my_cube = new Cube();

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	Camera cameraTest = Camera(0, 0, 3, 0, 0, -1, 0, 1, 0);

	double oldCurrentTime = glfwGetTime();

	
	///RENDER TEXTURE///
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	Texture my_texture = Texture();
	my_texture.emptyTexture(SCR_WIDTH, SCR_HEIGHT);

	Texture my_texture2 = Texture();
	my_texture2.getFromFile("data/images/tochos.jpg");

	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, my_texture.textureID, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{

		View = cameraTest.getCameraMatrix();

		glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 dirLight = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 pointLight = glm::vec3(0.0f, 2.0f, -2.0f);

		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		my_shader.useShader();

		my_shader.setUniform("M", Model);
		my_shader.setUniform("V", View);
		my_shader.setUniform("P", Projection);
		my_shader.setUniform("lightColor", lightColor);
		my_shader.setUniform("dirLight", dirLight);
		my_shader.setUniform("pointLight", pointLight);
		my_shader.setUniform("cameraPos", cameraTest.position);

		my_cube->draw();

		my_shader.stopShader();

		glDisableVertexAttribArray(0);

		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		plane_shader.useShader();

		// Bind our texture in Texture Unit 0
		my_texture.useTexture();
		// Set our "renderedTexture" sampler to use Texture Unit 0
		plane_shader.setUniform("renderedTexture", 0);
		plane_shader.setUniform("time", (float)(glfwGetTime()* 10.0f));

		my_plane->draw();
		my_texture.stopTexture();
		

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
		processInput(window, &cameraTest, deltaTime);

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
