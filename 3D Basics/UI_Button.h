#pragma once
#include "GameObject.h"

class TextLabel;
class AudioSound;
class AudioSystem;

class UI_Button : public GameObject
{
public:
	UI_Button(std::string menuTitle, glm::vec2 position);
	virtual ~UI_Button();

	virtual void Initialise() override;
	virtual void Render(GLuint program) override;
	void Update(float deltaTime);

	// Design
	void AdjustButtonPosition();
	void SetScale(float scale);
	void SetFont(std::string font);
	void SetText(std::string text);


	// Interaction
	bool IsClicked() const;
	bool IsSelected() const;
	void SetIsSelected(bool isSelected);
	void SetIsClicked(bool isClicked);
	void Reset();

	

private:

	glm::vec2 positionOnScreen;
	bool isClicked;
	bool isSelected;
	TextLabel * button = NULL;

};

