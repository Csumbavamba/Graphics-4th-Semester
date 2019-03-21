#include "ControlsScene.h"

#include "UI_Button.h"
#include "UI_Image.h"
#include "Utility.h"
#include "AudioSound.h"
#include "Input.h"
#include "SceneManager.h"

ControlsScene::ControlsScene()
{
	backButton = new UI_Button("MAIN MENU", glm::vec2(0.0f, 0.0f));
	backgroundImage = new UI_Image(mainCamera, "Sprites/PlaceHolder_Controls.jpg", Utility::GetScreenSize());

	// Setup Audio
	clickSound = new AudioSound("Audio/Click.wav", FMOD_DEFAULT);
	clickSound->SetAudioSystem(audioSystem);
	clickSound->Initialise();

	sceneName = "ControlsScene"; // TODO Create method to get this from file
}


ControlsScene::~ControlsScene()
{
	delete backButton;
	backButton = NULL;

	delete backgroundImage;
	backgroundImage = NULL;

	delete clickSound;
	clickSound = NULL;
}

void ControlsScene::Initialise()
{
	backButton->Initialise();
	backgroundImage->Initialise();
}

void ControlsScene::Render(GLuint program)
{
	backgroundImage->Render(NULL);
	backButton->Render(NULL);
}

void ControlsScene::Update(float deltaTime)
{
	// First call
	Scene::Update(deltaTime);

	backgroundImage->Update(deltaTime);
	backButton->Update(deltaTime);

	// Check when Enter is pressed
	if (Input::GetKeyState(13) == DOWN_FIRST)
	{
		// Switch Scene
		SceneManager::ChangeActiveScene("StartMenuScene");
	}
}
