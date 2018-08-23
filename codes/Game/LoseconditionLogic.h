/******************************************************************************/
/*!
\file   LoseconditionLogic.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Lose condition game logic header file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include  "Factory.h"
#include "GameLogicSystem.h"

namespace TE
{
	enum DyingPlace
	{
		EN_LEFT_X,
		EN_RIGHT_X,
		EN_UP_Y,
		EN_DOWN_Y
	};

	class LoseconditionLogic : public GameLogicSystem
	{
	public:
		LoseconditionLogic();
		void Initialize() override;
		void Update(float dt) override;
		void Free(void) override;
		~LoseconditionLogic();
		bool isBoundaryLose;
		bool IsLoseSoundPlayed = true;
		bool IsElec = false;
		bool IsFalling = false;
		bool IsBoxDie = false;
	private:
		float _fourPoints[4];

		unsigned FallSound;
	};


	extern LoseconditionLogic* LOSECONDITIONLOGIC;

}

