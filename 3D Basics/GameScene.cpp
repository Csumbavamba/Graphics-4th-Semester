#include "GameScene.h"

#include "ShaderedCube.h"
#include "Utility.h"
#include "Input.h"
#include "Skybox.h"
#include "ShaderLoader.h"
#include "SceneManager.h"
#include "WaterObject.h"


GameScene::GameScene()
{
	sceneName = "GameScene";

	skyBoxProgram = ShaderLoader::GetInstance()->CreateProgram("SkyBox-VS.vs", "SkyBox-FS.fs");
	fogProgram = ShaderLoader::GetInstance()->CreateProgram("FogShader.vs", "FogShader.fs");

	cube = new ShaderedCube(mainCamera);
	skybox = new Skybox(mainCamera);

	// Water effects
	waterTop = new WaterObject(mainCamera);
	waterTop->transform.rotation.x = +90.f;
	waterTop->transform.position.z += 5.0f;

	isScissorEnabled = false;
}


GameScene::~GameScene()
{
	delete cube;
	cube = NULL;

	delete skybox;
	skybox = NULL;

	delete waterTop;
	waterTop = NULL;
}

void GameScene::Initialise()
{
	cube->Initialise();
	skybox->Initialise();
	waterTop->Initialise();
}

void GameScene::Render(GLuint program)
{
	// skybox->Render(skyBoxProgram);

	cube->Render(fogProgram);

	waterTop->Render(program);
	
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	// skybox->Update();

	cube->Update(deltaTime);
	waterTop->Update(deltaTime);

	// mainCamera->RotateAroundObject(cube->transform.position, 3.0f, deltaTime);

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
	if (Input::GetKeyState('w') == DOWN_FIRST)
	{
		// Swap between outlined and not outlined
		cube->SetIsOutlined(!cube->IsOutlined());
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

