#pragma once
#include "Scene.h"

class GameMenu;

class ShaderedCube;
class WaterObject;
class WaterPool;

class StartMenuScene :
	public Scene
{
public:
	StartMenuScene();
	virtual ~StartMenuScene();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

private:
	
	GameMenu * startMenu = NULL;

	

	// Water Shading background
	WaterPool * pool = NULL;
	ShaderedCube * cube = NULL;
};

