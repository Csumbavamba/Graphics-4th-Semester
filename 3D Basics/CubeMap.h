#pragma once
#include "Camera.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <vector>
#include "string.h"
#include "Mesh_Cube.h"

//class Mesh_Cube;

class CubeMap : public Mesh_Cube
{
public:
	CubeMap(GameObject * owner, std::vector <std::string> vectorOfFilePaths);
	//~CubeMap();

	virtual void Initialise() override;
	virtual void Render(Camera * camera, GLuint program) override;
	virtual ~CubeMap();

	virtual GLuint GetTexture();

private:
	GLuint texID;
};

