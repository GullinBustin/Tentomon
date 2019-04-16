#pragma once
#include "base/Mesh.h"

class Plane :
	public Mesh
{
public:
	Plane();
	~Plane();
	void draw();
};

