#include "GameScene.h"

#include "ShaderedCube.h"


GameScene::GameScene()
{
	sceneName = "GameScene";

	cube = new ShaderedCube(mainCamera);
}


GameScene::~GameScene()
{
	delete cube;
	cube = NULL;
}

void GameScene::Initialise()
{
	cube->Initialise();
}

void GameScene::Render(GLuint program)
{
	cube->Render(program);
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	cube->Update(deltaTime);
	
	mainCamera->RotateAroundObject(cube->transform.position, 10.0f, deltaTime);
}
