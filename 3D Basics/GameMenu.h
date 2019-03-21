#pragma once
#include "GameObject.h"

class UI_Button;
class UI_Image;
class Camera;
class AudioSystem;
class AudioSound;

class GameMenu :
	public GameObject
{
public:
	GameMenu(Camera * mainCamera, AudioSystem * audioSystem);
	virtual ~GameMenu();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	void Update(float deltaTime);
	void Reset();

	void SetupAudio(AudioSystem * audioSystem);
	void ProcessKeyboardNavigation();
	void ProcessKeyboardClicks();
	void ChangeSelectedButton(int change);
	void ActOnMenuChoice();
	void ClickButton();

private:

	UI_Button * buttons[4];
	int buttonSelected;
	
	UI_Button * startButton = NULL;
	UI_Button * controlsButton = NULL;
	UI_Button * creditsButton = NULL;
	UI_Button * quitButton = NULL;

	AudioSound * clickSound = NULL;
	AudioSound * swapSound = NULL;
	UI_Image * backgroundImage = NULL;

};

