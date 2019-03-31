#pragma once
#include "GameObject.h"

class Mesh2D_Quad;
class Camera;

class WaterObject :
	public GameObject
{
public:
	WaterObject(Camera  * mainCamera);
	virtual ~WaterObject();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

private:
	Mesh2D_Quad * mesh = NULL;
};

