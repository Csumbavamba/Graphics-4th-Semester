#include "GameScene.h"

#include "ShaderedCube.h"
#include "Utility.h"
#include "Input.h"
#include "Skybox.h"
#include "ShaderLoader.h"
#include "SceneManager.h"


GameScene::GameScene()
{
	sceneName = "GameScene";

	skyBoxProgram = ShaderLoader::GetInstance()->CreateProgram("SkyBox-VS.vs", "SkyBox-FS.fs");

	cube = new ShaderedCube(mainCamera);
	skybox = new Skybox(mainCamera);

	isScissorEnabled = false;
}


GameScene::~GameScene()
{
	delete cube;
	cube = NULL;

	delete skybox;
	skybox = NULL;
}

void GameScene::Initialise()
{
	cube->Initialise();
	skybox->Initialise();
}

void GameScene::Render(GLuint program)
{
	// skybox->Render(skyBoxProgram);

	cube->Render(program);
	
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	// skybox->Update();

	cube->Update(deltaTime);

	mainCamera->RotateAroundObject(cube->transform.position, 3.0f, deltaTime);

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

}

