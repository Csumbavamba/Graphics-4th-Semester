#include "Camera.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


#include "Utility.h"
#include "Input.h"


Camera::Camera()
{
	viewMode = ORTOGRAPHIC;

}

Camera::Camera(ViewMode viewMode)
{
	this->viewMode = viewMode;

	cameraPosition = glm::vec3(1.0f, 1.0f, 10.0f);
	cameraLookDirection = glm::vec3(-0.1f, -0.1f, -1.0f);
	cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

}


Camera::~Camera()
{
}

void Camera::Initialise()
{
	timeElapsed = 0.0f;
	// Create Projection
	if (viewMode == PERSPECTIVE)
	{
		CreatePerspectiveProjection();
	}
	else
	{
		CreateOrthographicProjection();
	}
		
	

	// Generate PV
	CreatePV();
}

void Camera::Update(float deltaTime)
{
	// Last call
	CreatePV();

	ProcessArrowMovement(deltaTime);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

glm::mat4 Camera::GetPV() const
{
	return PV;
}


void Camera::CreatePerspectiveProjection()
{
	projectionMatrix = (glm::perspective(120.0f, (float)Utility::GetScreenWidth() / (float)Utility::GetScreenHeight(), 0.1f, 15000.0f));
}

void Camera::CreateOrthographicProjection()
{
	float halfScreenWidth = (float)(Utility::GetScreenWidth() / 2);
	float halfScreenHeight = (float)(Utility::GetScreenHeight() / 2);

	projectionMatrix = (glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 1000.0f));
}

void Camera::CreatePV()
{
	viewMatrix = (glm::lookAt(cameraPosition, cameraPosition + cameraLookDirection, cameraUpDirection));

	PV = projectionMatrix * viewMatrix;
}

void Camera::SetCameraPosition(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
}

void Camera::SetCameraLookDirection(glm::vec3 cameraLookDirection)
{
	this->cameraLookDirection = cameraLookDirection;
}

void Camera::SetCameraUpDirection(glm::vec3 cameraUpDirection)
{
	this->cameraUpDirection = cameraUpDirection;
}

glm::vec3 Camera::GetCameraPosition() const
{
	return cameraPosition;
}

glm::vec3 Camera::GetCameraLookDirection() const
{
	return cameraLookDirection;
}

glm::vec3 Camera::GetCameraUpDirection() const
{
	return cameraUpDirection;
}

void Camera::RotateAroundObject(glm::vec3 objectLocation, float distanceFromObject, float deltaTime)
{
	timeElapsed += deltaTime;

	float xMovement = sin(timeElapsed) * distanceFromObject;
	float zMovement = cos(timeElapsed) * distanceFromObject;
	float cameraY = 0.5f * distanceFromObject;

	// cameraUpDirection = glm::vec3(0.0, 1.0, 0.0);
	cameraPosition = glm::vec3(objectLocation.x + xMovement, cameraY, objectLocation.z + zMovement);
	cameraLookDirection = objectLocation - cameraPosition;
}

void Camera::FollowObject(glm::vec3 objectLocation)
{
	cameraPosition = glm::vec3(objectLocation.x, cameraPosition.y, objectLocation.z);
	cameraLookDirection = glm::vec3(objectLocation.x, cameraLookDirection.y, objectLocation.z);
}

void Camera::ProcessArrowMovement(float deltaTime)
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

void Camera::Reset()
{
	cameraPosition = glm::vec3(1.0f, 1.0f, 10.0f);
	cameraLookDirection = glm::vec3(-0.1f, -0.1f, -1.0f);
	cameraUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}
