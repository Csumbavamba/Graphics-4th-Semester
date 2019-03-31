#include "StartMenuScene.h"

#include "GameMenu.h"
#include "Camera.h"

#include "WaterObject.h"
#include "WaterPool.h"
#include "ShaderedCube.h"


StartMenuScene::StartMenuScene()
{
	startMenu = new GameMenu(mainCamera, audioSystem);

	cube = new ShaderedCube(mainCamera);

	// Water effects
	pool = new WaterPool(mainCamera);
	pool->transform.position.y -= 2.0f;

	sceneName = "StartMenuScene"; // TODO Create method to get this from file
}


StartMenuScene::~StartMenuScene()
{
	delete startMenu;
	startMenu = NULL;

	delete cube;
	cube = NULL;

	delete pool;
	pool = NULL;
}

void StartMenuScene::Initialise()
{
	startMenu->Initialise();
	pool->Initialise();
	cube->Initialise();
}

void StartMenuScene::Render(GLuint program)
{
	
	pool->Render(program);
	cube->Render(program);

	startMenu->Render(program);
}

void StartMenuScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	pool->Update(deltaTime);
	cube->Update(deltaTime);

	startMenu->Update(deltaTime);

	mainCamera->RotateAroundObject(cube->transform.position, 10.0f, deltaTime);
}

