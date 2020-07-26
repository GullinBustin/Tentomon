#include "Cube.h"

static const float vertex_array[] = {
	-1.0f,-1.0f,-1.0f, // triángulo 1 : comienza
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triángulo 1 : termina
	1.0f, 1.0f,-1.0f, // triángulo 2 : comienza
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triángulo 2 : termina
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

static const float normal_array[] = {
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-0.0f, 0.0f, -1.0f,
	-0.0f, 0.0f, -1.0f,
	-0.0f, 0.0f, -1.0f,
	0.0f, -1.0f, -0.0f,
	0.0f, -1.0f, -0.0f,
	0.0f, -1.0f, -0.0f,
	0.0f, -0.0f, -1.0f,
	0.0f, -0.0f, -1.0f,
	0.0f, -0.0f, -1.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-0.0f, -1.0f, 0.0f,
	-0.0f, -1.0f, 0.0f,
	-0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f
};


Cube::Cube()
{

	vertices = std::vector<float>(6*3*2*6, 0.0f); // 6 floats for each vertex, 3 vertex for each triangle, 2 triangles for each face, 6 faces for cube.

	for (int i = 0; i < 3 * 2 * 6; i++) {
		vertices[i * 6] = vertex_array[i * 3];
		vertices[i * 6 + 1] = vertex_array[i * 3 + 1];
		vertices[i * 6 + 2] = vertex_array[i * 3 + 2];
		vertices[i * 6 + 3] = normal_array[i * 3];
		vertices[i * 6 + 4] = normal_array[i * 3 + 1];
		vertices[i * 6 + 5] = normal_array[i * 3 + 2];
	}

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
		6*sizeof(float),    // Paso
		(void*)0            // desfase del buffer
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
		3,                                // tamaño
		GL_FLOAT,                         // tipo
		GL_TRUE,                         // normalizado?
		6 * sizeof(float),                // corrimiento
		(void*) (3 * sizeof(float))       // corrimiento de buffer
	);

	glBindVertexArray(0);

}

void Cube::draw() {

	glBindVertexArray(VAO);
	//glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);

	//glDisableVertexAttribArray(0);
}

void Cube::drawInstances(int n) {
	glBindVertexArray(VAO);
	//glEnableVertexAttribArray(0);

	//glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 3 * 2 * 6, n);

	//glDisableVertexAttribArray(0);
}

Cube::~Cube()
{
}
