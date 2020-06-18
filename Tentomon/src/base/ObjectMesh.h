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

    const aiScene* my_scene;
};

