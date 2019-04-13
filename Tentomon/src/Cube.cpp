#include "Cube.h"


static const float vertex_array_normal[] = {
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

static const float vertex_array[] = {
	-1.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,
	 1.0f,  1.0f, 1.0f,
	-1.0f,  1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f
};
static const unsigned int element_array[] = {
	0, 1, 2,
	0, 2, 3,
	4, 7, 6,
	4, 6, 5,
	0, 3, 7,
	0, 7, 4,
	1, 6, 2,
	1, 5, 6,
	0, 4, 5,
	0, 5, 1,
	3, 6, 7,
	3, 2, 6
};


Cube::Cube(bool normals)
{
	withNormals = normals;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	if (!normals)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array), vertex_array, GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array_normal), vertex_array_normal, GL_STATIC_DRAW);

	if (!normals) {
		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element_array), element_array, GL_STATIC_DRAW);
	}
	else {
		glGenBuffers(1, &normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normal_array), normal_array, GL_STATIC_DRAW);
	}
}

void Cube::draw() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		1,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
		3,                                // tamaño
		GL_FLOAT,                         // tipo
		GL_FALSE,                         // normalizado?
		0,                                // corrimiento
		(void*)0                          // corrimiento de buffer
	);

	if (!withNormals) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glDrawElements(GL_TRIANGLES, 3 * 2 * 6, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, 3*2*6);
	}


	glDisableVertexAttribArray(0);
}


Cube::~Cube()
{
}
