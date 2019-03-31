#pragma once

#include <string>

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Transform.h"

class Camera;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise() {};
	virtual void Render(GLuint program) = 0;
	virtual void Update(float deltaTime) {};

	void SetCamera(Camera * camera);
	
	void SetActive(bool isActive);
	bool IsActive() const;

	Transform transform;

protected:
	Camera * camera = NULL;
	bool isActive;
	
};

