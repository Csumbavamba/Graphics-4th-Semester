#pragma once
#include "GameObject.h"

class TextLabel;

class UI_Text : public GameObject
{
public:
	UI_Text(std::string menuTitle, glm::vec2 position);
	virtual ~UI_Text();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	void Update();

	void SetFont(std::string font);
	void SetText(std::string text);
	void SetColor(glm::vec3 color);
	void SetScale(float scale);

private:
	TextLabel * text = NULL;
};

