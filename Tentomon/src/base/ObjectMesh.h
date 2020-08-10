#pragma once
#include "Mesh.h"
#include <assimp/scene.h>

class ObjectMesh :
    public Mesh
{
public:
    ObjectMesh(const aiScene* scene, int mesh_index = 0);
    ~ObjectMesh();

    void draw();

    void drawInstances(int n);

    const aiScene* my_scene;

private:
    void fillVertexMesh(aiMesh* theMesh, int vertex_step, int normal_step, int uv_step, int color_step);
    void fillVertexMultiMesh(const aiScene* scene, bool normals, bool UVs, bool colors);

};

