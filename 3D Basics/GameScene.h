#pragma once
#include "Scene.h"

class ShaderedCube;

class GameScene :
	public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

private:
	// Gonna need to have a camera
	ShaderedCube * cube = NULL;
};

