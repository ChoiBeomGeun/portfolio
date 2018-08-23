/******************************************************************************/
/*!
\file   Soundmanager.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Sound Manager source file in the engine system class */
/******************************************************************************/

#include "SoundManager.h"
#include "DebugUtil.h"
#include  "fmod.h"

#include "fmod.hpp"
#include "fmod_errors.h"
#include  "DebugUtil.h"
using namespace TE;


namespace TE {
	SoundManager * SOUNDMANAGER = nullptr;
}
SoundManager::SoundManager()
{
	DEBUG_ASSERT(SOUNDMANAGER != nullptr, "Factory already created! There can only be 1");
	SOUNDMANAGER = this;





}
SoundManager::~SoundManager()
{
	system->release();
	system->close();
	
}




void SoundManager::Initialize(void)
{
	result = FMOD::System_Create(&system);
	ERRORCheck(result);

	result = system->getVersion(&version);
	ERRORCheck(result);

	if (version < FMOD_VERSION)
	{
		printf("FMOD is low version");
		
	}

	result = system->init(32, FMOD_INIT_NORMAL,0);
	ERRORCheck(result);
}

void SoundManager::Update(float dt)
{
	dt = dt;
	if (b_SoundOnOff) {
		system->update();
	}
}

void SoundManager::DeleteSounds(void)
{
	if (b_SoundOnOff) {
		for (auto iSound : Sounds)
		{
			result = iSound->release();
		
			ERRORCheck(result);
		}
		if(Sounds.size()>0)
 		Sounds.erase(Sounds.begin(), Sounds.end());
		if (Channels.size()>0)
		Channels.erase(Channels.begin(), Channels.end());
		Sounds.clear();
		Channels.clear();
		
		soundID = 0;
		added = false;
	}
}



void SoundManager::ERRORCheck(FMOD_RESULT presult)
{
	if (presult != FMOD_OK)
	{
		DEBUG_ASSERT("FMOD error! (%d) %s\n", FMOD_ErrorString(result));
		exit(-1);
	}
}

SOUNDID SoundManager::LoadSound(std::string SoundDir)
{


	std::string saveLevel = SoundDir;

	SoundDir = ".\\sounds.\\" + SoundDir;

	if (b_SoundOnOff)
	{
		if (added) {
			soundID++;
			added = false;
		}

		FMOD::Sound* sound = 0;
		FMOD::Channel* channel = 0;


		Sounds.push_back(sound);
		Channels.push_back(channel);
		FMOD_RESULT volume = Channels[soundID]->setVolume(1.f);
		Volume.push_back((const float)volume);

		result = system->createSound(SoundDir.c_str(), FMOD_HARDWARE, 0, &Sounds[soundID]);
		ERRORCheck(result);
		added = true;

		return soundID;
	}
	return (SOUNDID)-1;
}

void SoundManager::PlaySounds(unsigned int soundtoplay, bool IsRepeat )
{
	if (b_SoundOnOff) {
		if (!IsRepeat)
			Sounds[soundtoplay]->setMode(FMOD_LOOP_OFF);
		else
			Sounds[soundtoplay]->setMode(FMOD_LOOP_NORMAL);
		result = system->playSound(FMOD_CHANNEL_FREE, Sounds[soundtoplay], false, &Channels[soundtoplay]);
		
		bool bplay;

		Channels[soundtoplay]->isPlaying(&bplay);




		ERRORCheck(result);
	}
}

void TE::SoundManager::PlayOnceSounds(unsigned int soundtoplay, bool IsRepeat, bool & IsPlayed)
{
	if (IsPlayed) {
		if (b_SoundOnOff) {
			if (!IsRepeat)
				Sounds[soundtoplay]->setMode(FMOD_LOOP_OFF);
			else
				Sounds[soundtoplay]->setMode(FMOD_LOOP_NORMAL);
			result = system->playSound(FMOD_CHANNEL_FREE, Sounds[soundtoplay], false, &Channels[soundtoplay]);

			bool bplay;

			Channels[soundtoplay]->isPlaying(&bplay);




			ERRORCheck(result);
		}
	}
	IsPlayed = false;
}

void SoundManager::StopSound(SOUNDID soundtostop)
{
	
	if (b_SoundOnOff) {
		Channels[soundtostop]->setPaused(true);
		ERRORCheck(result);
	}

}

void SoundManager::ResumeSound(SOUNDID soundtostop)
{

	if (b_SoundOnOff) {
		Channels[soundtostop]->setPaused(false);
		ERRORCheck(result);
	}

}

void TE::SoundManager::PauseAllSound(void)
{
	if (b_SoundOnOff) {
		for (auto it : Channels)
		{
			it->setPaused(true);
 			ERRORCheck(result);
		}
	}
}

void TE::SoundManager::ResumeAllSound(void)
{
	if (b_SoundOnOff) {
		for (auto it : Channels)
		{
			it->setPaused(false);
			ERRORCheck(result);
		}
	}
}


void SoundManager::SetVolume(SOUNDID soundtoadjust, float volume)
{
	Channels[soundtoadjust]->setVolume(volume);


}



