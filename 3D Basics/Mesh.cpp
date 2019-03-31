#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "GameObject.h"

#include <iostream>

Mesh::Mesh()
{
	texture = new Texture();
	texture->SetTexturePath("Sprites/Rayman.jpg");
	texture->Initialise();

	cameraPosition = glm::vec3(1.0f, 1.0f, 10.0f);
}


Mesh::~Mesh()
{
	delete texture;
	texture = NULL;
}

void Mesh::Render(Camera * camera, GLuint program)
{
	glUseProgram(program);

	// Add texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	// Get values to send to shaders
	PVM = camera->GetPV() * modelMatrix;
	
	// Provide PVM
	GLuint PVMLoc = glGetUniformLocation(program, "PVM");
	glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(PVM));

	// Provide Model
	GLuint ModelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	// TEST!!!!!
	// Provide View
	GLuint viewLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Provide Projection
	GLuint projectionLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
	// TEST!!!!!


	// Proved Camera Position
	cameraPosition = camera->GetCameraPosition();
	GLuint camPos = glGetUniformLocation(program, "camPos");
	glUniform3fv(camPos, 1, glm::value_ptr(cameraPosition));

	

	// Draw Object
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Mesh::ReflectionRender(Camera * camera, GLuint program, GLuint textureID)
{
	glUseProgram(program);

	// Add texture
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	glUniform1i(glGetUniformLocation(program, "skybox"), 0);

	PVM = camera->GetPV() * modelMatrix;

	// Provide PVM
	GLuint PVMLoc = glGetUniformLocation(program, "PVM");
	glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(PVM));

	//Provide CamPos
	cameraPosition = camera->GetCameraPosition();
	GLuint camPos = glGetUniformLocation(program, "camPos");
	glUniformMatrix4fv(camPos, 1, GL_FALSE, glm::value_ptr(cameraPosition));
	
	// Provide Model
	GLuint ModelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Draw Object
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Mesh::Update()
{
	CalculateModelMatrix();
}

Texture * Mesh::GetTexture() const
{
	return texture;
}

void Mesh::CalculateModelMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), owner->transform.position);
	glm::mat4 rotationmatrix = owner->transform.CalculateRotationMatrix();
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(), owner->transform.scale); // TODO add scaling

	// Model																																					
	modelMatrix = translationMatrix * rotationmatrix * scalingMatrix;
}
