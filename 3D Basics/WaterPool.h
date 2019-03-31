#pragma once
#include "GameObject.h"

class WaterObject;
class PoolWall;

class WaterPool :
	public GameObject
{
public:
	WaterPool(Camera  * mainCamera);
	virtual ~WaterPool();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

private:

	PoolWall * bottom = NULL;
	PoolWall * left = NULL;
	PoolWall * right = NULL;
	PoolWall * front = NULL;
	PoolWall * back = NULL;

	WaterObject * water = NULL;

	GameObject * poolObjects[6];
};

