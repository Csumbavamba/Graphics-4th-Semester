#pragma once

#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

enum ViewMode
{
	PERSPECTIVE,
	ORTOGRAPHIC
};

class Camera
{
public:
	Camera();
	Camera(ViewMode viewMode);
	virtual ~Camera();

	void Initialise();
	virtual void Update(float deltaTime);

	virtual glm::mat4 GetViewMatrix() const;
	virtual glm::mat4 GetProjectionMatrix() const;
	virtual glm::mat4 GetPV() const;

	virtual void SetCameraPosition(glm::vec3 cameraPosition);
	virtual void SetCameraLookDirection(glm::vec3 cameraLookDirection);
	virtual void SetCameraUpDirection(glm::vec3 cameraUpDirection);

	virtual glm::vec3 GetCameraPosition() const;
	virtual glm::vec3 GetCameraLookDirection() const;
	virtual glm::vec3 GetCameraUpDirection() const;

	virtual void RotateAroundObject(glm::vec3 objectLocation, float distanceFromObject, float deltaTime);
	virtual void FollowObject(glm::vec3 objectLocation);

	// Movement
	void ProcessArrowMovement(float deltaTime);
	void Reset();


protected:
	glm::vec3 cameraPosition;
	glm::vec3 cameraLookDirection;
	glm::vec3 cameraUpDirection;

	// Matrix creation
	void CreatePerspectiveProjection();
	void CreateOrthographicProjection();
	void CreatePV();

	ViewMode viewMode;
	float timeElapsed;

	// Stored matricies
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 PV;

};

