#pragma once

#include <string>
#include "Dependencies\fmod\fmod.hpp"

class AudioSystem;

class AudioSound
{
public:
	AudioSound();
	AudioSound(std::string filePath, FMOD_MODE playMode);
	~AudioSound();

	void Initialise();

	void SetAudioSystem(AudioSystem * system);

	FMOD::Sound * GetSound() const;
	void SetSound(FMOD::Sound *);
	FMOD_MODE GetPlayMode() const;
	std::string GetFilePath() const;

	void PlaySound();
	void ReleaseSound();

private:
	std::string filePath;
	FMOD_MODE playMode;
	FMOD::Sound * sound = NULL;

	AudioSystem * system = NULL;
};

