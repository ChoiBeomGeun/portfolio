/******************************************************************************/
/*!
\file   InGameLogic.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

InGameLogic System header file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
/******************************************************************************/

#pragma once
#include <vector>
#include  "GameLogicSystem.h"

namespace  TE {
	class InGameLogic
	{
	public:
		InGameLogic();
		~InGameLogic();

		void InGameInit(void);
		void InGameUpdate(float dt);
		bool InGameDelay(float  dt, float howlong);
		void InGameShutdown(void);	
		void InGameLogicAdd(GameLogicSystem * game_logic_system);
		void DestoryAllGameLogics(void);
		std::vector<GameLogicSystem*> GameLogicList;

		std::vector<std::string> vsLevelList;
	private:
		float temp;
	};

	extern InGameLogic* INGAMELOGIC;
}