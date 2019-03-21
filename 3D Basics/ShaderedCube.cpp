#include "ShaderedCube.h"

#include "Mesh_Cube.h"


ShaderedCube::ShaderedCube(Camera * mainCamera)
{
	camera = mainCamera;
	mesh = new Mesh_Cube(this);
}


ShaderedCube::~ShaderedCube()
{
	delete mesh;
	mesh = NULL;
}

void ShaderedCube::Initialise()
{
	mesh->Initialise();
}

void ShaderedCube::Render(GLuint program)
{
	mesh->Render(camera, program);
}

void ShaderedCube::Update(float deltaTime)
{
	mesh->Update();
}
