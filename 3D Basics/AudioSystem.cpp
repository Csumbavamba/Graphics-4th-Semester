#include "AudioSystem.h"
#include "AudioSound.h"

#include "Dependencies\fmod\fmod.hpp"



AudioSystem::AudioSystem()
{
	Initialise();
}


AudioSystem::~AudioSystem()
{
	audioSystem->release();
}

bool AudioSystem::Initialise()
{
	// Create audio system
	FMOD_RESULT createdSystem;
	createdSystem = FMOD::System_Create(&audioSystem);

	if (createdSystem != FMOD_OK)
		return false;

	// Setup audio system
	createdSystem = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);

	if (createdSystem != FMOD_OK)
		return false;

	return true;
}


void AudioSystem::Update(float deltaTime)
{
	audioSystem->update();
}

bool AudioSystem::CreateSound(AudioSound * sound)
{
	FMOD_RESULT createdSound;

	FMOD::Sound * tempSound = nullptr;

	createdSound = audioSystem->createSound(
		sound->GetFilePath().c_str(),
		sound->GetPlayMode(),
		NULL,
		&tempSound // TODO check if it works
		
	);

	sound->SetSound(tempSound);

	if (createdSound != FMOD_OK)
		return false;
	return true;
	
}

void AudioSystem::PlaySound(AudioSound * sound)
{
	FMOD_RESULT playedSound;

	playedSound = audioSystem->playSound(sound->GetSound(), 0, false, 0);
}

void AudioSystem::ReleaseSound(AudioSound * sound)
{
	FMOD_RESULT releasedSound;

	releasedSound = sound->GetSound()->release();
}
