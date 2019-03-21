#pragma once

#include "Dependencies\fmod\fmod.hpp"

class AudioSound;

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	
	void Update(float deltaTime);

	bool CreateSound(AudioSound * sound);
	void PlaySound(AudioSound * sound);
	void ReleaseSound(AudioSound * sound);

private:

	bool Initialise();
	FMOD::System * audioSystem = nullptr;
};

