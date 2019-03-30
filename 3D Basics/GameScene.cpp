#include "GameScene.h"

#include "ShaderedCube.h"
#include "Utility.h"
#include "Input.h"
#include "Skybox.h"
#include "ShaderLoader.h"


GameScene::GameScene()
{
	sceneName = "GameScene";

	skyBoxProgram = ShaderLoader::GetInstance()->CreateProgram("SkyBox-VS.vs", "SkyBox-FS.fs");

	cube = new ShaderedCube(mainCamera);
	skybox = new Skybox(mainCamera);

	isScissorEnabled = false;
	isStencilEnabled = true;

	stencilPass = 1;
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
	skybox->Render(skyBoxProgram);

	if (isStencilEnabled)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		// First pass
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		cube->Render(program);

		// Second pass
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);

		cube->Render(program);

		glDisable(GL_STENCIL_TEST);
	}

	
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	skybox->Update();

	cube->Update(deltaTime);

	// mainCamera->RotateAroundObject(cube->transform.position, 10.0f, deltaTime);

	ProcessScissorInput();
}

void GameScene::ProcessScissorInput()
{
	if (Input::GetKeyState('w') == DOWN_FIRST)
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

