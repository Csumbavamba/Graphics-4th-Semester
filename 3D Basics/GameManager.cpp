#include "GameManager.h"

#include "Camera.h"
#include "ShaderLoader.h"
#include "Utility.h"
#include "Input.h" 
#include "AudioSystem.h"

// Scenes
#include "Scene.h"
#include "SceneManager.h"
#include "ControlsScene.h"
#include "StartMenuScene.h"
#include "CreditsScene.h"
#include "GameScene.h"

#pragma comment(lib, "Ws2_32.lib")

GameManager * GameManager::instance = NULL;

GameManager::GameManager()
{
	deltaTime = 0.0f;

	// Create Scenes
	startMenuScene = new StartMenuScene();
	startMenuScene->SetIsActiveScene(true);
	creditsScene = new CreditsScene();
	controlsScene = new ControlsScene();
	gameScene = new GameScene();
	
	// Push Scenes into the scene Holder
	scenes.push_back(startMenuScene);
	scenes.push_back(creditsScene);
	scenes.push_back(controlsScene);
	scenes.push_back(gameScene);

	SceneManager::AddScenes(scenes);
}


GameManager::~GameManager()
{
	// Scenes
	for (Scene * scene : scenes)
	{
		delete scene;
		scene = NULL;
	}

	scenes.clear();

	// Static Deletes
	SceneManager::ShutDown();
	ShaderLoader::ShutDown();
	Input::ShutDown();
	Utility::ShutDown();
}

GameManager * GameManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}
	return instance;;
}

void GameManager::PlayGame(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Dwarf Game II");

	glClearColor(1.0, 0.0, 0.0, 1.0); // Clear Window


	glewInit(); // ADD FUNCTIONS AFTER THIS

	//// Enable Culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK); 

	//// Enable Depth for Rendering -- See if that causes error
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Blend between textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GetInstance()->Initialise();

	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	// Input stuff
	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);
	glutSpecialFunc(Input::SpecialKeyboardDown);
	glutSpecialUpFunc(Input::SpecialKeyboardUp);
	glutMouseFunc(Input::MouseClick);
	glutMotionFunc(Input::MouseActiveMove);
	glutPassiveMotionFunc(Input::MousePassiveMove);

	glutCloseFunc(GameManager::ShutDownGame);
	glutMainLoop();

	return;
}

void GameManager::Initialise()
{
	// Create Programs
	program = ShaderLoader::GetInstance()->CreateProgram("VertexShader.vs", "FragmentShader.fs");

	// Deltatime calculation
	previousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);

	// Initialize the Scenes
	for (Scene * scene : scenes)
	{
		scene->Initialise();
	}

}

void GameManager::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); // clear red

	
	// Do rendering here - Render Current Scene
	SceneManager::GetActiveScene()->Render(GetInstance()->program);

	glBindVertexArray(0); // Unbind VAO
	glUseProgram(0);

	glutSwapBuffers();
}

void GameManager::Update()
{
	// Time Calculation
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->deltaTime = (currentTime - GetInstance()->previousTimeStamp) * 0.001f;
	GetInstance()->previousTimeStamp = currentTime;

	// Update Screen size
	Utility::Update();

	// Update the Current Scene
	SceneManager::GetActiveScene()->Update(GetInstance()->deltaTime);

	// Last function call
	glutPostRedisplay();
}

void GameManager::QuitGame()
{
	glutLeaveMainLoop();
}


void GameManager::ShutDownGame()
{
	delete instance;
	instance = NULL;
}

