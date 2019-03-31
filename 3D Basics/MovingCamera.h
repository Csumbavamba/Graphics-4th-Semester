#pragma once
#include "Camera.h"


class MovingCamera :
	public Camera
{
public:
	MovingCamera();
	virtual ~MovingCamera() {};

	virtual void Update(float deltaTime) override;

	// Movement
	void ProcessArrowMovement(float deltaTime);
	void Reset();
};

