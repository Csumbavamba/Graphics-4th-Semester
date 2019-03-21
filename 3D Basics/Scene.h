#pragma once

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <string>

class AudioSystem;
class Camera;


class Scene
{
public:

	Scene();
	virtual~Scene();

	virtual void Initialise() = 0;
	virtual void Render(GLuint program) = 0;
	virtual void Update(float deltaTime);

	bool IsActiveScene() const;
	void SetIsActiveScene(bool isActiveScene);

	std::string GetSceneName() const;

protected:

	bool isActiveScene = false;
	Camera * mainCamera = NULL;
	AudioSystem * audioSystem = NULL;
	std::string sceneName = ""; // TODO Create method to get this by code (without the .cpp or .h

};

