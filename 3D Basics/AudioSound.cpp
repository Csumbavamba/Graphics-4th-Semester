#include "AudioSound.h"
#include "AudioSystem.h"

#include "Dependencies\fmod\fmod.hpp"



AudioSound::AudioSound()
{
}

AudioSound::AudioSound(std::string filePath, FMOD_MODE playMode)
{
	this->filePath = filePath;
	this->playMode = playMode;
}


AudioSound::~AudioSound()
{
	sound->release();
}

void AudioSound::Initialise()
{
	system->CreateSound(this);
}

void AudioSound::SetAudioSystem(AudioSystem * system)
{
	this->system = system;
}

FMOD_MODE AudioSound::GetPlayMode() const
{
	return playMode;
}

std::string AudioSound::GetFilePath() const
{
	return filePath;
}

void AudioSound::PlaySound()
{
	system->PlaySound(this);
}

void AudioSound::ReleaseSound()
{
	system->ReleaseSound(this);
	// sound->release();
}

FMOD::Sound * AudioSound::GetSound() const
{
	return sound;
}

void AudioSound::SetSound(FMOD::Sound * sound)
{
	this->sound = sound;
}
