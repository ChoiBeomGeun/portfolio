/******************************************************************************/
/*!
\file   Soundmanager.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Sound Manager header file in the engine system class */
/******************************************************************************/
#pragma once





#ifndef BG_SOUNDMANAGER_H
#define BG_SOUNDMANAGER_H


#include <vector>
#include "System.h"
#include  "BaseStage.h"
#include  "GameStateList.h"
#include <fmod.h>
#include <fmod.hpp>
typedef unsigned int SOUNDID;
namespace TE {

	class SoundManager :public Systems {
	public:
		SoundManager();
		~SoundManager();
		void ERRORCheck(FMOD_RESULT result);
		SOUNDID LoadSound(std::string  SoundDir);
		void PlaySounds(unsigned int soundtoplay,bool IsRepeat);

		void PlayOnceSounds(unsigned int soundtoplay, bool IsRepeat, bool & IsPlayed);
		void StopSound(SOUNDID soundtostop);
		void SetVolume(SOUNDID soundtoadjust, float volume);
		void Initialize(void) override;
		void Update(float dt) override;
		bool added= false;
		void DeleteSounds(void);
		void SoundOn(void) { b_SoundOnOff = true; }
		void SoundOff(void) { b_SoundOnOff = false; }
		void ResumeSound(SOUNDID soundtostop);
		bool SoundOnOffCheck(void) { return b_SoundOnOff; }
		void PauseAllSound(void);
		void ResumeAllSound(void);
		SOUNDID soundID = 0;
		std::vector<float> Volume;
	private:
		std::vector<FMOD::Sound*> Sounds;
		std::vector<FMOD::Channel*>Channels;
		bool b_SoundOnOff = true;
		FMOD::System *system;
		FMOD_RESULT result;
	
		unsigned int version;
		int key = 0;
	};


	extern SoundManager* SOUNDMANAGER;
}
#endif