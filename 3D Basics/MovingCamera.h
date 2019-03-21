#pragma once
#include "GameObject.h"

class Camera;

class MovingCamera : public GameObject
{
public:
	MovingCamera();
	virtual ~MovingCamera();

private:

	Camera * camera = NULL;
};

