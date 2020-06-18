#include "ObjectMesh.h"

ObjectMesh::ObjectMesh(const aiScene* scene, int mesh_index)
{
	my_scene = scene;
	aiMesh* theMesh = scene->mMeshes[mesh_index];

	vertices = std::vector<float>(theMesh->mNumVertices * 8, 0.0f);
	indices = std::vector<unsigned int>(theMesh->mNumFaces * 3, 0.0f);

	aiVector3D* obj_vertex = theMesh->mVertices;
	aiVector3D* obj_normals = theMesh->mNormals;
	aiVector3D* obj_uv = theMesh->mTextureCoords[0];
	aiFace* obj_faces = theMesh->mFaces;

	for (int i = 0; i < theMesh->mNumVertices; i++) {
		vertices[i * 8] = obj_vertex[i].x;
		vertices[i * 8 + 1] = obj_vertex[i].y;
		vertices[i * 8 + 2] = obj_vertex[i].z;

		vertices[i * 8 + 3] = obj_normals[i].x;
		vertices[i * 8 + 4] = obj_normals[i].y;
		vertices[i * 8 + 5] = obj_normals[i].z;

		vertices[i * 8 + 6] = obj_uv[i].x;
		vertices[i * 8 + 7] = obj_uv[i].y;
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
		8 * sizeof(float),    // Paso
		(void*)0            // desfase del buffer
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
		3,                                // tamaño
		GL_FLOAT,                         // tipo
		GL_TRUE,                         // normalizado?
		8 * sizeof(float),                // corrimiento
		(void*)(3 * sizeof(float))       // corrimiento de buffer
	);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
		2,                                // tamaño
		GL_FLOAT,                         // tipo
		GL_TRUE,                         // normalizado?
		8 * sizeof(float),                // corrimiento
		(void*)(6 * sizeof(float))       // corrimiento de buffer
	);

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
