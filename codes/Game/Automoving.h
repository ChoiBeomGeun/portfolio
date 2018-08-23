/******************************************************************************/
/*!
\file	Automoving.h
\author	 Choi Beom Geun
\par	email: hyunjun306@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/12/16

This is Automoving header interface
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/


#pragma once
#include  "Factory.h"
#include "GameLogicSystem.h"

namespace TE
{
	class AutoMovingLogic : public GameLogicSystem
	{
	public:
		AutoMovingLogic();
		void Initialize() override;
		void Update(float dt) override;
		void Free(void) override;
		~AutoMovingLogic();

	private:


	};


	extern AutoMovingLogic* AUTOMOVINGLOGIC;

}

