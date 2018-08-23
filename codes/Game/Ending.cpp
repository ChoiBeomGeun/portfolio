/******************************************************************************/
/*!
\file	Ending.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29
	
Ending
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Ending.h"
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
#include "Graphics.h"
using namespace TE;
Jsonclass fileending;
int autoindexE = 0;
bool GoLeft = true;
int transindex = 21;
float transv = 0;
bool IsOut = false;
unsigned int endingsound;
Ending::Ending()
{

}

Ending::~Ending()
{
}

void Ending::Load()
{
	STATEMANAGER->IsEnding = true;
	STATEMANAGER->IsEndingISOVER = true;
	std::string saveLevele = "SAVE";
	LEVELMANAGER->LoadLevel("Ending.json");

	if(APP->IsKRMODE)
		FACTORY->ObjectIDMap[21]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("kr_credit1.png");


	FACTORY->ObjectIDMap[21]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 0);
	FACTORY->ObjectIDMap[21]->GetComponent<Transform>()->SetScale(glm::vec3(
		FACTORY->ObjectIDMap[21]->GetComponent<Transform>()->GetScale().x-500, 
		FACTORY->ObjectIDMap[21]->GetComponent<Transform>()->GetScale().y,
		FACTORY->ObjectIDMap[21]->GetComponent<Transform>()->GetScale().z
	));
	FACTORY->ObjectIDMap[22]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 0);
	FACTORY->ObjectIDMap[23]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 0);
	FACTORY->ObjectIDMap[24]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 0);
	fileending.ReadFile(".\\autoplays.\\" + saveLevele);
	endingsound = SOUNDMANAGER->LoadSound("Endingsound.mp3");

}

void Ending::Init()
{
	SOUNDMANAGER->PlaySounds(endingsound, false);
	autoindexE = 0;
	transindex = 21;
	transv = 0;
	IsOut = false;
}

void Ending::Update(float dt)
{
	if (Input::IsTriggered(SDL_SCANCODE_ESCAPE))
	{

		STATEMANAGER->MoveState(StatesList::Menu);
		STATEMANAGER->IsEnding = false;
	}
	dt = dt;

	float XposE = fileending.mRoot["PositionX"][autoindexE].asFloat();
	float YposE = fileending.mRoot["PositionY"][autoindexE].asFloat();
	
	
		FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->SetPosition(glm::vec3(XposE, YposE, 0));
		FACTORY->ObjectIDMap[17]->GetComponent<Transform>()->SetPosition(glm::vec3(XposE + 90, YposE, 0));

		if ((int)FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->GetPosition().x== 526)
			GoLeft = false;
		if ((int)FACTORY->ObjectIDMap[13]->GetComponent<Transform>()->GetPosition().x == -592)
			GoLeft = true;

			if (GoLeft) {
			
				autoindexE++;
			}
			else
				autoindexE--;

			if (transv >= 255.f)
			{
				IsOut = true;
			}

			if (transv == 0 && IsOut)
			{
				IsOut = false;
				FACTORY->Destroy(FACTORY->ObjectIDMap[transindex]);
				transindex++;
				if (transindex == 25)
				{
	
					STATEMANAGER->MoveState(StatesList::Menu);
					STATEMANAGER->IsEnding = false;
					
				}
			}
			if (IsOut)
				transv -= 1;
			else
				transv += 1;
			if (transindex != 25)
			FACTORY->ObjectIDMap[transindex]->GetComponent<Sprite>()->ChangeAvalue(transv);
}

void Ending::Free(void)
{

}



void Ending::Unload()
{
;
}