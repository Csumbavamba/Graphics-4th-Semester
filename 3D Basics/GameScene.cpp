#include "GameScene.h"

#include "ShaderedCube.h"
#include "Utility.h"
#include "Input.h"
#include "Skybox.h"
#include "ShaderLoader.h"
#include "SceneManager.h"
#include "WaterObject.h"
#include "WaterPool.h"


GameScene::GameScene()
{
	sceneName = "GameScene";

	skyBoxProgram = ShaderLoader::GetInstance()->CreateProgram("SkyBox-VS.vs", "SkyBox-FS.fs");
	fogProgram = ShaderLoader::GetInstance()->CreateProgram("FogShader.vs", "FogShader.fs");

	cube = new ShaderedCube(mainCamera);
	cubeTwo = new ShaderedCube(mainCamera);

	cubeTwo->transform.position.x += 0.5f;
	cubeTwo->transform.position.z += 0.5f;
	cubeTwo->transform.position.y += 0.5f;

	skybox = new Skybox(mainCamera);

	// Water effects
	pool = new WaterPool(mainCamera);
	pool->transform.position.y -= 2.0f;

	isScissorEnabled = false;
}


GameScene::~GameScene()
{
	delete cube;
	cube = NULL;

	delete cubeTwo;
	cubeTwo = NULL;

	delete skybox;
	skybox = NULL;

	delete pool;
	pool = NULL;
}

void GameScene::Initialise()
{
	cube->Initialise();
	cubeTwo->Initialise();
	skybox->Initialise();
	pool->Initialise();
}

void GameScene::Render(GLuint program)
{
	// skybox->Render(skyBoxProgram);

	cube->Render(fogProgram);
	cubeTwo->Render(fogProgram);

	pool->Render(program);
	
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);


	cube->Update(deltaTime);
	cubeTwo->Update(deltaTime);
	pool->Update(deltaTime);

	ProcessScissorInput();
	ProcessStencilInput();
	LookForPauseInput();

	
}

void GameScene::ProcessScissorInput()
{
	if (Input::GetKeyState('q') == DOWN_FIRST)
	{
		// If Key is pressed enable or disable Scissor Test
		if (isScissorEnabled)
		{
			glDisable(GL_SCISSOR_TEST);
			isScissorEnabled = false;
		}
		else
		{
			glEnable(GL_SCISSOR_TEST);
			glScissor(0, 0, Utility::GetScreenWidth(), Utility::GetScreenHeight() / 2);
			isScissorEnabled = true;
		}
	}
}

void GameScene::ProcessStencilInput()
{
	if (Input::GetKeyState('e') == DOWN_FIRST)
	{
		// Swap between outlined and not outlined
		cube->SetIsOutlined(!cube->IsOutlined());
		cubeTwo->SetIsOutlined(!cubeTwo->IsOutlined());
	}
}

void GameScene::LookForPauseInput()
{
	// If Escape is clicked
	if (Input::GetKeyState(27) == DOWN_FIRST)
	{
		ResetScene();
		SceneManager::ChangeActiveScene("StartMenuScene");
	}
}

void GameScene::ResetScene()
{
	// Reset Scissors
	glDisable(GL_SCISSOR_TEST);
	isScissorEnabled = false;

	// Reset Outline
	cube->SetIsOutlined(false);

	// Reset Camera
	mainCamera->Reset();
}

