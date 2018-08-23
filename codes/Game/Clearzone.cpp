/******************************************************************************/
/*!
\file	Clearzone.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Clear zone game logic source file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Clearzone.h"
#include  "Factory.h"
#include  "InGameLogic.h"
#include "Application.h"
#include "Input.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "ParticleManager.h"
#include "LevelManager.h"
using namespace TE;
static Object *player;
static Object *obj;
Object * clearparticle;
SOUNDID WinSound;


namespace TE {
	ClearzoneLogic * CLEARZONELOGIC = nullptr;
}




ClearzoneLogic::ClearzoneLogic()
{
	CLEARZONELOGIC = this;

	
}
void ClearzoneLogic::Initialize()
{
	OnceWin = true;
	WinSound = SOUNDMANAGER->LoadSound("portalintro.mp3");
	player = FACTORY->GetPlayer();
	obj = GetClearzone();
	clearparticle = FACTORY->CreateHUD(obj->GetComponent<Transform>()->position, obj->GetComponent<Transform>()->scale);
	clearparticle->GetComponent<Sprite>()->isPerspective = true;
	PARTICLEMANAGER->LoadEmitter(clearparticle, "finish.json");
	SoundIsPlay = true;
 }



void ClearzoneLogic::Update(float dt)
{
for (auto Objects : FACTORY->ObjectIDMap)
	{

		if (Objects.second->objectstyle == Objectstyle::Clearzone)
			obj = Objects.second;

	}
if (APP->b_Win) {
	
	player->GetComponent<Transform>()->angle += TUMath::GetRandomInt(300, 800) * dt;

	player->GetComponent<Transform>()->scale -= TUMath::GetRandomInt(50, 150) * dt;
	player->GetComponent<Transform>()->rotation += dt;
}
	if (obj != NULL)
		obj->GetComponent<Transform>()->angle += 20 * dt;
	if (obj != NULL)
	{
		player = FACTORY->GetPlayer();
		if (!APP->b_Lose &&PHYSICS->RectvsRectCollisionCheck(player->GetComponent<Transform>(), obj->GetComponent<Transform>()))
		{
			SOUNDMANAGER->PlayOnceSounds(WinSound, false, SoundIsPlay);
	
			if (OnceWin) {
				APP->b_Win = true;

				OnceWin = false;

				STATEMANAGER->b_IsDelay = true;
			}
			
		}
	}
}


Object* ClearzoneLogic::GetClearzone(void)
{

	for (auto Objects : FACTORY->ObjectIDMap)
	{

		if (Objects.second->objectstyle == Objectstyle::Clearzone)
			return Objects.second;
	}
	return NULL;
}
void TE::ClearzoneLogic::Free(void)
{
	PARTICLEMANAGER->Delete_all_particles();
	SOUNDMANAGER->DeleteSounds();
}
ClearzoneLogic::~ClearzoneLogic()
{
}