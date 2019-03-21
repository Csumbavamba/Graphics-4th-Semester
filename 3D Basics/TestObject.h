#pragma once

#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include "Transform.h"
#include "GameObject.h"

#include <string>

class Mesh2D_Quad;


class TestObject : public GameObject
{
public:
	TestObject(Camera * camera);
	virtual ~TestObject();

	virtual void Initialise() override;

	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime);

	// TODO move into mesh
	void AddTexturePath(std::string path);


private:
	Mesh2D_Quad * mesh = NULL;
};

