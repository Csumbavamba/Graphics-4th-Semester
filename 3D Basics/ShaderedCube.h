#pragma once
#include "GameObject.h"

class Mesh_Cube;

class ShaderedCube :
	public GameObject
{
public:
	ShaderedCube(Camera * mainCamera);
	virtual ~ShaderedCube();

	virtual void Initialise() override;
	virtual void Render(GLuint program);
	
	virtual void Update(float deltaTime);

	void SetIsOutlined(bool isOutlined);
	bool IsOutlined() const;


private:

	Mesh_Cube * mesh = NULL;
	void RenderMeshOutline(const GLuint &program);

	GLuint outlineProgram;
	bool isOutlined;

};

