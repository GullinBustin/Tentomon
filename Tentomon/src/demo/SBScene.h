#pragma once
#include "../base/Scene.h"
#include "../base/Instance.h"

class SBScene :
    public Scene
{
public:
	SBScene();
	~SBScene();
	void setup();
	void draw(double currentTime);
	Instance planeInstance;
};

