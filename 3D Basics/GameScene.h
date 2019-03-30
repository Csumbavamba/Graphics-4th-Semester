#pragma once
#include "Scene.h"

//#include "Dependencies\soil\SOIL.h"
//#include "Dependencies\glew\glew.h"
//#include "Dependencies\freeglut\freeglut.h"

class ShaderedCube;
class Skybox;

class GameScene :
	public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

	void ProcessScissorInput();


private:
	// Gonna need to have a camera
	ShaderedCube * cube = NULL;

	GLuint skyBoxProgram;
	Skybox * skybox = NULL;

	bool isScissorEnabled;
	bool isStencilEnabled;
	int stencilPass;
};

