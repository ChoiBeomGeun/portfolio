/******************************************************************************/
/*!
\file	Intro.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Intro
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Intro.h"
#include <stdio.h>
#include "Object.h"
#include "Factory.h"
#include "Input.h"
#include "StateManager.h"
#include "Engine.h"
#include  "LevelManager.h"
#include  <string>
#include "Application.h"
#include "SoundManager.h"
#include "InGameLogic.h"
#include "LevelList.h"
#include "StateLists.h"
#include "Archetype.h"
#include "ParticleManager.h"
using namespace TE;
Jsonclass fileIntro;
Json::Value rootIntro;
int autoindex = 0;
bool Enter = false;
bool once = true;
SOUNDID backsound;
SOUNDID blackhole;
Object * particleintro;
Intro::Intro()
{

}

Intro::~Intro()
{
}

void Intro::Load()
{
	LEVELMANAGER->LoadLevel("intro.json");

}

void Intro::Init()
{
	once = true;
	std::string saveLevel = "SAVE";

	backsound = SOUNDMANAGER->LoadSound("introback.mp3");
	blackhole = SOUNDMANAGER->LoadSound("portalintro.mp3");


	 
	fileIntro.ReadFile(".\\autoplays.\\" + saveLevel);


	 SOUNDMANAGER->PlaySounds(backsound,false);

}

void Intro::Update(float dt)
{

	FACTORY->ObjectIDMap[14]->GetComponent<Transform>()->angle += 300 * dt;
	static bool stop = true;

	if (Input::IsTriggered(SDL_SCANCODE_R))
	{
		stop = true;
		autoindex = 0;
	}

	if (Input::IsTriggered(SDL_SCANCODE_Y))
	{
		

		stop = false;

	}

	dt = dt;
	float Xpos = fileIntro.mRoot["PositionX"][autoindex].asFloat();
	float Ypos = fileIntro.mRoot["PositionY"][autoindex].asFloat();

	if (stop) {

		if (!(int(FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->position.x) > 200)) {
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->SetPosition(glm::vec3(Xpos, Ypos, 0));
		
		}
		else
			Enter = true;
		if(!(int(FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->position.x) ==171 && ((int)FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->position.y == -255)))
		FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->SetPosition(glm::vec3(Xpos + 90, Ypos, 0));
	}

	if(Enter)
	{
		if (once) {
			SOUNDMANAGER->PlaySounds(blackhole, false);
	
			once = false;
		}
		camActIntro.ShakeCamera(dt);
		if (FACTORY->ObjectIDMap[14]->GetComponent<Transform>()->position.x >
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->position.x) {
			FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->position.x += dt * 100;
			FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->angle += 300 * dt;
			FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->scale -= 100 * dt;
			FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->rotation += dt ;

			FACTORY->ObjectIDMap[18]->GetComponent<Transform>()->position.x += dt * 300;
			FACTORY->ObjectIDMap[18]->GetComponent<Transform>()->angle += 300 * dt;
			FACTORY->ObjectIDMap[18]->GetComponent<Transform>()->scale -= 100 * dt;
			FACTORY->ObjectIDMap[18]->GetComponent<Transform>()->rotation += dt;

			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->position.x += dt * 100;
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->angle += 300 * dt;
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->scale -= 100 * dt;
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->rotation += dt;
		}
		if (FACTORY->ObjectIDMap[14]->GetComponent<Transform>()->position.y >
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->position.y) {
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->position.y += dt * 100;
			FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->rotation += dt ;



		}



	}

	autoindex++;

	if (CAMERA->cameraPos.z == 0 || Input::IsAnyTriggered()) {


		STATEMANAGER->MoveState(StatesList::Splash);

	}

}

void Intro::Free(void)
{
	printf("IntroFree\n");
	Enter = false;
}



void Intro::Unload()
{
	printf("IntroUnload\n");
}