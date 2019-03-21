#include "UI_Text.h"
#include "TextLabel.h"



UI_Text::UI_Text(std::string menuTitle, glm::vec2 position)
{
	std::string font = "Dependencies/Fonts/SnackerComic.ttf";
	text = new TextLabel(menuTitle, font, position);
}


UI_Text::~UI_Text()
{
	delete text;
	text = NULL;
}

void UI_Text::Initialise()
{
	text->Initialise();
}

void UI_Text::Render(GLuint program)
{
	text->Render(NULL);
}

void UI_Text::Update()
{
	text->Update();
}

void UI_Text::SetFont(std::string font)
{
	text->SetFont(font);
}

void UI_Text::SetText(std::string text)
{
	this->text->SetText(text);
}

void UI_Text::SetColor(glm::vec3 color)
{
	text->SetColor(color);
}

void UI_Text::SetScale(float scale)
{
	text->SetScale(scale);
}

