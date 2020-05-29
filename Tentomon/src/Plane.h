#pragma once
#include "base/Mesh.h"
#include "base/Singleton.h"

class Plane :
	public Mesh, public Singleton<Plane>
{
public:
	friend class Singleton<Plane>;
	Plane();
	~Plane();
	void draw();
};

