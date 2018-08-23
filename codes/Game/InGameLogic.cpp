/******************************************************************************/
/*!
\file	InGameLogic.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

InGameLogic System source file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
/******************************************************************************/

#include "InGameLogic.h"
#include  "Trigger.h"
#include  "Clearzone.h"
#include  "Factory.h"
#include "StateManager.h"
#include "Trigger.h"
#include "Application.h"
#include "LoseconditionLogic.h"
#include "logging.h"
#include "engine.h"
using namespace  TE;


void* operator new(std::size_t sz, char * ch, long line) {
	std::printf("File name : %s\n Code line :  %d", ch, line);
	std::printf("global op new called, size = %zu\n", sz);
	return std::malloc(sz);
}


namespace TE {


	InGameLogic * INGAMELOGIC = nullptr;


}
InGameLogic::InGameLogic()
{
	if(ENGINE->IsLoggingOn)
  	LOGGINGSYSTEM = new LoggingSystem;
	INGAMELOGIC = this;
	temp = 0;
}

InGameLogic::~InGameLogic()
{


}

void InGameLogic::InGameInit()
{

	for (auto IngameLogics : GameLogicList)
		IngameLogics->Initialize();
	bool b_playerExist = false;
	bool b_colorzoneExist = false;
	for (auto Objects : FACTORY->ObjectIDMap)
	{
		if (FACTORY->GetPlayer())
			b_playerExist = true;
		if (FACTORY->ObjectIDMap[Objects.first]->objectstyle == Objectstyle::Clearzone)
			b_colorzoneExist = true;
	}

	if (!(b_playerExist || b_colorzoneExist))
	APP->b_Win = false;
	APP->b_Lose = false;
	
	if(ENGINE->IsLoggingOn)
	LOGGINGSYSTEM->Initialize();
}
void InGameLogic::InGameLogicAdd(GameLogicSystem * game_logic_system)
{
	GameLogicList.push_back(game_logic_system);

}
void TE::InGameLogic::DestoryAllGameLogics(void)
{

	for (unsigned i = 0; i <GameLogicList.size(); ++i)
	{
		delete GameLogicList[GameLogicList.size() - 1 - i];

	}
	GameLogicList.erase(GameLogicList.begin(), GameLogicList.end());
	
}
void InGameLogic::InGameUpdate(float dt)
{
	for (auto IngameLogics : GameLogicList)
		IngameLogics->Update(dt);
	if (ENGINE->IsLoggingOn)
	LOGGINGSYSTEM->Update(dt);

	for (auto Objects : FACTORY->ObjectIDMap)
	{
		if (STATEMANAGER->b_IsRotating)
			if (FACTORY->ObjectIDMap[Objects.first]->objectstyle == Objectstyle::Box || FACTORY->ObjectIDMap[Objects.first]->objectstyle == Objectstyle::AttachBox)
				FACTORY->ObjectIDMap[Objects.first]->GetComponent<Body>()->pm_velocity = glm::vec3(0);
	}
}

bool InGameLogic::InGameDelay(float  dt, float howlong)
{
	temp += dt * 2;
	
		if (temp > howlong)
		{
			temp = 0;
			return false;
		}
		else 
		{			
			return true;;
		}
	
}

void InGameLogic::InGameShutdown(void)
{
#ifdef _DEBUG 
	for (auto IngameLogics : GameLogicList)
		IngameLogics->Free();
#endif

}
