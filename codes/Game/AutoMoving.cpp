/******************************************************************************/
/*!
\file	Automoving.cpp
\author	 Choi Beom Geun
\par	email: hyunjun306@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/12/16

This is Automoving implementation.
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/


#include "Trigger.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "Timer.h"
#include "PlayerController.h"
#include "Automoving.h"
#include "cAutoMoving.h"

using namespace TE;
std::vector<Object*> VoAutoMovingObjects;

namespace TE {
	AutoMovingLogic * AUTOMOVINGLOGIC = nullptr;
}




AutoMovingLogic::AutoMovingLogic()
{

	AUTOMOVINGLOGIC = this;


}
void AutoMovingLogic::Initialize(void)
{
	//Finding Movingthings
	for(auto oMovingthings : FACTORY->ObjectIDMap)
	{
		if (oMovingthings.second->HasComponent<AutoMoving>())
			VoAutoMovingObjects.push_back(oMovingthings.second);

	}

}

void AutoMovingLogic::Update(float dt)
{
	for(auto oMovingthing : VoAutoMovingObjects )
	{
		/////////////Setting Init Position
		if (oMovingthing->GetComponent<Transform>()->GetPosition().x == oMovingthing->GetComponent<AutoMoving>()->mPaths
			[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.x
			&&
		oMovingthing->GetComponent<Transform>()->GetPosition().y == oMovingthing->GetComponent<AutoMoving>()->mPaths
				[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.y)
		{
			oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath++;
			
		}
		///////////// Moving X pos
			if (oMovingthing->GetComponent<Transform>()->GetPosition().x <= oMovingthing->GetComponent<AutoMoving>()->mPaths
				[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.x)
			{
				oMovingthing->GetComponent<Transform>()->position.x += dt * 200.f;
			}

			if (oMovingthing->GetComponent<Transform>()->GetPosition().x >= oMovingthing->GetComponent<AutoMoving>()->mPaths
				[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.x)
			{
				oMovingthing->GetComponent<Transform>()->position.x -= dt * 200.f;
			}
		///////////// Moving Y pos

			if (oMovingthing->GetComponent<Transform>()->GetPosition().y <= oMovingthing->GetComponent<AutoMoving>()->mPaths
				[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.y)
			{
				oMovingthing->GetComponent<Transform>()->position.y += dt * 200.f;
			}


			if (oMovingthing->GetComponent<Transform>()->GetPosition().y >= oMovingthing->GetComponent<AutoMoving>()->mPaths
				[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.y)
			{
				oMovingthing->GetComponent<Transform>()->position.y -= dt * 200.f;
			}
		///////////// Path Checking and continue Next path
			if (((abs(oMovingthing->GetComponent<Transform>()->GetPosition().x - oMovingthing->GetComponent<AutoMoving>()->mPaths
				[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.x)) <= 0.1f &&
				(abs( oMovingthing->GetComponent<Transform>()->GetPosition().y - oMovingthing->GetComponent<AutoMoving>()->mPaths
					[oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath].pathway.y)) <= 0.1f)) {

				
				oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath++;
				if (oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath >= oMovingthing->GetComponent<AutoMoving>()->mPaths.size())
					oMovingthing->GetComponent<AutoMoving>()->NumberOfTowardPath = 0;
				}
			/////////////
	}
}

void AutoMovingLogic::Free(void)
{
	VoAutoMovingObjects.clear();
}


AutoMovingLogic::~AutoMovingLogic()
{
}
