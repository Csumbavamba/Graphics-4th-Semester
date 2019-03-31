#include "MovingCamera.h"
#include "Input.h"


MovingCamera::MovingCamera()
{
	this->viewMode = PERSPECTIVE;

	cameraPosition = glm::vec3(1.0f, 1.0f, 10.0f);
	cameraLookDirection = glm::vec3(-0.1f, -0.1f, -1.0f);
	cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	Initialise();
}



void MovingCamera::Update(float deltaTime)
{
	Camera::Update(deltaTime);

	ProcessArrowMovement(deltaTime);
}

void MovingCamera::ProcessArrowMovement(float deltaTime)
{
	float movement = 0.0f;

	if (Input::GetKeyState('w') == DOWN)
	{
		// Keep removing from camera z position
		movement = -1.0f * deltaTime;
	}
	else if (Input::GetKeyState('s') == DOWN)
	{
		// Keep adding to camera z position
		movement = 1.0f * deltaTime;
	}

	cameraPosition = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z + movement);
}

void MovingCamera::Reset()
{
	cameraPosition = glm::vec3(1.0f, 1.0f, 10.0f);
	cameraLookDirection = glm::vec3(-0.1f, -0.1f, -1.0f);
	cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}
