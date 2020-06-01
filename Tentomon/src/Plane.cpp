#include "Plane.h"



Plane::Plane()
{
	vertices = std::vector<float>{-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	                               1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	                              -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
								   1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	                               1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
								  -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		6 * sizeof(float),    // Paso
		(void*)0            // desfase del buffer
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
		3,                                // tamaño
		GL_FLOAT,                         // tipo
		GL_FALSE,                         // normalizado?
		6 * sizeof(float),                // corrimiento
		(void*)(3 * sizeof(float))       // corrimiento de buffer
	);

	glBindVertexArray(0);
}


Plane::~Plane()
{
}

void Plane::draw() {

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_PATCHES, 0, 3 * 2);

	glDisableVertexAttribArray(0);
}