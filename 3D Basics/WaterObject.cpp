#include "WaterObject.h"
#include "Mesh2D_Quad.h"
#include "Texture.h"


WaterObject::WaterObject(Camera  * mainCamera)
{
	camera = mainCamera;

	mesh = new Mesh2D_Quad(this);
	mesh->GetTexture()->SetTexturePath("Sprites/water.png");

	transform.scale *= 2.0f;
}


WaterObject::~WaterObject()
{

	delete mesh;
	mesh = NULL;
}


void WaterObject::Initialise()
{
	mesh->Initialise();
}

void WaterObject::Render(GLuint program)
{
	mesh->Render(camera, program);
}

void WaterObject::Update(float deltaTime)
{
	mesh->Update();
}
