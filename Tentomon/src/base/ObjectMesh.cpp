#include "ObjectMesh.h"

ObjectMesh::ObjectMesh(const aiScene* scene, int mesh_index)
{
	my_scene = scene;
	aiMesh* theMesh = scene->mMeshes[mesh_index];

	bool UVs = theMesh->HasTextureCoords(0);
	bool normals = theMesh->HasNormals();
	bool colors = theMesh->HasVertexColors(0);
	int vertex_step = 12;
	int uv_step = 6;
	int normal_step = 3;
	int color_step = 8;
	if (!normals) {
		vertex_step -= 3;
		uv_step -= 3;
		color_step -= 3;
		normal_step = 0;
	}
	if (!UVs) {
		vertex_step -= 2;
		color_step -= 2;
		uv_step = 0;
	}
	if (!colors) {
		vertex_step -= 4;
		color_step = 0;
	}

	vertices = std::vector<float>(theMesh->mNumVertices * vertex_step, 0.0f);
	indices = std::vector<unsigned int>(theMesh->mNumFaces * 3, 0.0f);

	aiVector3D* obj_vertex = theMesh->mVertices;
	aiVector3D* obj_normals = theMesh->mNormals;
	aiVector3D* obj_uv = theMesh->mTextureCoords[0];
	aiColor4D* obj_color = theMesh->mColors[0];
	aiFace* obj_faces = theMesh->mFaces;

	for (int i = 0; i < theMesh->mNumVertices; i++) {
		vertices[i * vertex_step] = obj_vertex[i].x;
		vertices[i * vertex_step + 1] = obj_vertex[i].y;
		vertices[i * vertex_step + 2] = obj_vertex[i].z;
		if (normals) {
			vertices[i * vertex_step + normal_step] = obj_normals[i].x;
			vertices[i * vertex_step + 1 + normal_step] = obj_normals[i].y;
			vertices[i * vertex_step + 2 + normal_step] = obj_normals[i].z;
		}
		if (UVs) {
			vertices[i * vertex_step + uv_step] = obj_uv[i].x;
			vertices[i * vertex_step + 1 + uv_step] = obj_uv[i].y;
		}
		if (colors) {
			vertices[i * vertex_step + color_step] = obj_color[i].r;
			vertices[i * vertex_step + 1 + color_step] = obj_color[i].g;
			vertices[i * vertex_step + 2 + color_step] = obj_color[i].b;
			vertices[i * vertex_step + 3 + color_step] = obj_color[i].a;
		}
	}

	for (int i = 0; i < theMesh->mNumFaces; i++) {
		indices[i * 3] = obj_faces[i].mIndices[0];
		indices[i * 3 + 1] = obj_faces[i].mIndices[1];
		indices[i * 3 + 2] = obj_faces[i].mIndices[2];
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
		vertex_step * sizeof(float),    // Paso
		(void*)0            // desfase del buffer
	);
	if (normals) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
			3,                                // tamaño
			GL_FLOAT,                         // tipo
			GL_TRUE,                         // normalizado?
			vertex_step * sizeof(float),                // corrimiento
			(void*)(normal_step * sizeof(float))       // corrimiento de buffer
		);
	}
	if (UVs) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
			2,                                // tamaño
			GL_FLOAT,                         // tipo
			GL_FALSE,                         // normalizado?
			vertex_step * sizeof(float),                // corrimiento
			(void*)(uv_step * sizeof(float))       // corrimiento de buffer
		);
	}
	if (colors) {
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(
			4,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
			4,                                // tamaño
			GL_FLOAT,                         // tipo
			GL_FALSE,                         // normalizado?
			vertex_step * sizeof(float),                // corrimiento
			(void*)(color_step * sizeof(float))       // corrimiento de buffer
		);
	}

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}

ObjectMesh::~ObjectMesh()
{
}

void ObjectMesh::draw() {

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
}
