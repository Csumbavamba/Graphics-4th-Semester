#include "ShaderedCube.h"

#include "Mesh_Cube.h"
#include "ShaderLoader.h"



ShaderedCube::ShaderedCube(Camera * mainCamera)
{
	camera = mainCamera;
	mesh = new Mesh_Cube(this);

	isOutlined = false;

	outlineProgram = ShaderLoader::GetInstance()->CreateProgram("VertexShader.vs", "OutlineShader.fs");
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
	if (isOutlined)
	{
		RenderMeshOutline(program);
	}
	else
	{
		mesh->Render(camera, program);
	}

}

void ShaderedCube::RenderMeshOutline(const GLuint &program)
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should update the stencil buffer
	glStencilMask(0xFF); // enable writing to the stencil buffer

	mesh->Render(camera, program);

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00); // disable writing to the stencil buffer
	glDisable(GL_DEPTH_TEST);

	// Do outline mesh here
	transform.scale = glm::vec3(1.1f, 1.1f, 1.1f);
	mesh->Update();
	mesh->Render(camera, outlineProgram);

	// Set Values back
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	mesh->Update();

	glStencilMask(0xFF);
	glEnable(GL_DEPTH_TEST);
}

void ShaderedCube::Update(float deltaTime)
{
	mesh->Update();
}

void ShaderedCube::SetIsOutlined(bool isOutlined)
{
	this->isOutlined = isOutlined;
}

bool ShaderedCube::IsOutlined() const
{
	return isOutlined;
}
