#include "GameMenu.h"

#include "UI_Button.h"
#include "UI_Image.h"
#include "Camera.h"
#include "AudioSystem.h"
#include "AudioSound.h"
#include "Input.h"
#include "GameManager.h"
#include "SceneManager.h"

#include "Utility.h"
#include <iostream>


GameMenu::GameMenu(Camera * mainCamera, AudioSystem * audioSystem)
{
	this->camera = mainCamera;

	buttonSelected = 0;

	// Create buttons
	startButton = new UI_Button("START", glm::vec2(0.0f, 150.0f));
	controlsButton = new UI_Button("CONTROLS", glm::vec2(0.0f, 50.0f));
	creditsButton = new UI_Button("CREDITS", glm::vec2(0.0f, -50.0f));
	quitButton = new UI_Button("QUIT", glm::vec2(0.0f, -150.0f));

	// Move buttons into array for easier control
	buttons[0] = startButton;
	buttons[1] = controlsButton;
	buttons[2] = creditsButton;
	buttons[3] = quitButton;

	// Start is selected by default
	buttons[buttonSelected]->SetIsSelected(true);
	

	backgroundImage = new UI_Image(mainCamera, "Sprites/DwarfBackground2.jpg", Utility::GetScreenSize());
	clickSound = new AudioSound("Audio/Click.wav", FMOD_DEFAULT);
	swapSound = new AudioSound("Audio/Click2.wav", FMOD_DEFAULT);

	SetupAudio(audioSystem);
}


GameMenu::~GameMenu()
{
	delete backgroundImage;
	backgroundImage = NULL;

	for (int i = 0; i < 4; i++)
	{
		delete buttons[i];
		buttons[i] = NULL;
	}

	delete clickSound;
	clickSound = NULL; // TODO see if it needs to be released
}

void GameMenu::Initialise()
{
	backgroundImage->Initialise();

	startButton->Initialise();
	controlsButton->Initialise();
	creditsButton->Initialise();
	quitButton->Initialise();
}

void GameMenu::Render(GLuint program)
{
	if (isActive)
	{
		backgroundImage->Render(NULL);

		startButton->Render(NULL);
		controlsButton->Render(NULL);
		creditsButton->Render(NULL);
		quitButton->Render(NULL);
	}
}

void GameMenu::Update(float deltaTime)
{
	if (isActive)
	{
		backgroundImage->Update(deltaTime);

		startButton->Update(deltaTime);
		controlsButton->Update(deltaTime);
		creditsButton->Update(deltaTime);
		quitButton->Update(deltaTime);

		ProcessKeyboardNavigation();
		ProcessKeyboardClicks();
	}
}

void GameMenu::Reset()
{
	startButton->Reset();
	controlsButton->Reset();
	creditsButton->Reset();
	quitButton->Reset();

	isActive = true;

	// Start button is selected by default
	buttonSelected = 0;
	startButton->SetIsSelected(true);
}

void GameMenu::SetupAudio(AudioSystem * audioSystem)
{
	clickSound->SetAudioSystem(audioSystem);
	clickSound->Initialise();

	swapSound->SetAudioSystem(audioSystem);
	swapSound->Initialise();
}

void GameMenu::ProcessKeyboardNavigation()
{
	// If user clicks down, increase the selected numbers
	if (Input::GetSpecialKeyState(GLUT_KEY_DOWN) == DOWN_FIRST)
	{
		ChangeSelectedButton(+1);
	}
	// If user clicks up
	else if (Input::GetSpecialKeyState(GLUT_KEY_UP) == DOWN_FIRST)
	{
		ChangeSelectedButton(-1);
	}
}

void GameMenu::ProcessKeyboardClicks()
{
	// If Enter is pressed
	if (Input::GetKeyState(13) == DOWN_FIRST)
	{
		ClickButton();
		ActOnMenuChoice();
	}
}

void GameMenu::ChangeSelectedButton(int change)
{
	// Deselect the previous button
	buttons[buttonSelected]->SetIsSelected(false);

	buttonSelected += change;

	// Play click sound
	swapSound->PlaySound();

	// Lerp around if neccessary
	if (buttonSelected > 3)
	{
		buttonSelected = 0;
	}
	else if (buttonSelected < 0)
	{
		buttonSelected = 3;
	}

	// Select the new button
	buttons[buttonSelected]->SetIsSelected(true);
}

void GameMenu::ActOnMenuChoice()
{
	if (startButton->IsClicked())
	{
		SceneManager::ChangeActiveScene("GameScene");
	}
	if (controlsButton->IsClicked())
	{
		SceneManager::ChangeActiveScene("ControlsScene");
	}
	else if (creditsButton->IsClicked())
	{
		SceneManager::ChangeActiveScene("CreditsScene");
	}
	else if (quitButton->IsClicked())
	{
		// Quit Application
		GameManager::QuitGame();
	}

	Reset();
}

void GameMenu::ClickButton()
{
	clickSound->PlaySound();
	buttons[buttonSelected]->SetIsClicked(true);
}
