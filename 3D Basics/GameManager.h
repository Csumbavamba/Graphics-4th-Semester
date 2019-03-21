#pragma once

// Vertices and Textures
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <vector>
#include <thread>
#include <string>

class ShaderLoader;

class Scene;
class StartMenuScene;
class GameScene;

class GameManager
{
public:
	static GameManager * GetInstance();

	static void PlayGame(int argc, char **argv);
	void Initialise();
	static void Render();
	static void Update();
	
	static void QuitGame();


	float deltaTime;

private:

	// Singleton
	GameManager();
	~GameManager();
	GameManager(const GameManager& copy) {};
	GameManager& operator= (const GameManager& move) {};

	static void ShutDownGame();

	static GameManager * instance;

	GLuint program;
	
	// For deltatime
	float previousTimeStamp;

	StartMenuScene * startMenuScene = NULL;
	GameScene * gameScene = NULL;
	

	std::vector<Scene*> scenes;
};

