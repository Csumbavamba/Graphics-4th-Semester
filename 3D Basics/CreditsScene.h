#pragma once
#include "Scene.h"

class UI_Button;
class UI_Image;
class AudioSound;

class CreditsScene :
	public Scene
{
public:
	CreditsScene();
	virtual ~CreditsScene();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	virtual void Update(float deltaTime) override;

private:
	UI_Button * backButton = NULL;
	UI_Image * backgroundImage = NULL;
	AudioSound * clickSound = NULL;
};

