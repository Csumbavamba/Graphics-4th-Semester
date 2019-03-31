#include "UI_Button.h"
#include "TextLabel.h"
#include "Input.h"

#include "AudioSound.h"
#include "AudioSystem.h"



UI_Button::UI_Button(std::string menuTitle, glm::vec2 position)
{
	std::string font = "Dependencies/Fonts/DWARVESC.TTF";
	positionOnScreen = position;

	isClicked = false;
	isSelected = false;

	button = new TextLabel(menuTitle, font, position);
}


UI_Button::~UI_Button()
{
	delete button;
	button = NULL;
}

void UI_Button::Initialise()
{
	button->Initialise();

	AdjustButtonPosition();
}

void UI_Button::AdjustButtonPosition()
{
	// Move the text as the position given was it's center
	glm::vec2 adjustedPosition = glm::vec2(
		positionOnScreen.x - button->GetTextWidth() / 2,
		positionOnScreen.y - button->GetTextHeight() / 2);

	button->SetPosition(adjustedPosition);
}

void UI_Button::Render(GLuint program)
{
	button->Render(NULL);
}

void UI_Button::Update(float deltaTime)
{
	button->Update();
}


void UI_Button::SetScale(float scale)
{
	button->SetScale(scale);
}

void UI_Button::SetFont(std::string font)
{
	button->SetFont(font);
}

void UI_Button::SetText(std::string text)
{
	button->SetText(text);
}

bool UI_Button::IsClicked() const
{
	return isClicked;
}

bool UI_Button::IsSelected() const
{
	return isSelected;
}

void UI_Button::SetIsSelected(bool isSelected)
{
	this->isSelected = isSelected;

	// If it's not selected, highlight it
	if (isSelected)
	{
		button->SetScale(1.2f);
		button->SetColor(glm::vec3(0.0f, 0.0f, 0.0f));
		AdjustButtonPosition();
	}
	// Otherwise bring it back to normal
	else
	{
		button->SetScale(1.0f);
		button->SetColor(glm::vec3(0.2f, 0.2f, 0.2f));
		AdjustButtonPosition();
	}
}

void UI_Button::SetIsClicked(bool isClicked)
{
	this->isClicked = isClicked;
}


void UI_Button::Reset()
{
	isClicked = false;
	SetIsSelected(false);
}
