#include "Scene.h"




Scene::Scene()
{
	this->mainCamera = new Camera(PERSPECTIVE);
	this->audioSystem = new AudioSystem();

	mainCamera->Initialise();
}

Scene::~Scene()
{
	delete mainCamera;
	mainCamera = NULL;

	delete audioSystem;
	audioSystem = NULL;
}

void Scene::Update(float deltaTime)
{
	mainCamera->Update(deltaTime);
	audioSystem->Update(deltaTime);
}

bool Scene::IsActiveScene() const
{
	return isActiveScene;
}

void Scene::SetIsActiveScene(bool isActiveScene)
{
	this->isActiveScene = isActiveScene;
}

std::string Scene::GetSceneName() const
{
	return sceneName;
}
