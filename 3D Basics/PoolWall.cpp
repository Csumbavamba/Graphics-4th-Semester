#include "PoolWall.h"

#include "Mesh2D_Quad.h"
#include "Texture.h"

PoolWall::PoolWall(Camera  * mainCamera)
{
	camera = mainCamera;

	mesh = new Mesh2D_Quad(this);
	mesh->GetTexture()->SetTexturePath("Sprites/poolWall.jpg");

	transform.scale *= 2.0f;
}


PoolWall::~PoolWall()
{
	delete mesh;
	mesh = NULL;
}

void PoolWall::Initialise()
{
	mesh->Initialise();
}

void PoolWall::Render(GLuint program)
{
	glDisable(GL_CULL_FACE);
	mesh->Render(camera, program);
	glEnable(GL_CULL_FACE);
}

void PoolWall::Update(float deltaTime)
{
	mesh->Update();
}
