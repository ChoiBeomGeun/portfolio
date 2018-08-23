/******************************************************************************/
/*!
\file	Clearzone.h
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Clear zone game logic header file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#pragma once

#include  "GameLogicSystem.h"
#include "InGameLogic.h"
#include "Object.h"
namespace  TE 
{

	class ClearzoneLogic : public GameLogicSystem
	{
	public:
		//Initialize the system
		void Initialize() override;
		//All systems are updated every frames
		void Update(float dt) override;
		void Free(void) override;

		Object * GetClearzone(void);
		ClearzoneLogic();
		~ClearzoneLogic();
		bool   SoundIsPlay = true;
		bool OnceWin = true;

	};

	extern ClearzoneLogic* CLEARZONELOGIC;
}

