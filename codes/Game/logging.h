/******************************************************************************/
/*!
\file	logging.h
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Logging system for playtesting header file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include  "Factory.h"
#include "GameLogicSystem.h"
#include "json/json.h"
#include "json/JsonClass.h"
namespace TE
{
	class LoggingSystem
	{
	public:
		LoggingSystem();
		void Initialize() ;
		void Update(float dt) ;
		void Free(void) ;
		~LoggingSystem();
		long HowManyDies = 0;
		long HowMuchTimePassed = 0;
		bool IsLoggigOn = false;
		void SavingLog(void);
		Jsonclass files;
		Json::Value rootlog;


	};


	extern LoggingSystem*LOGGINGSYSTEM;

}


#pragma once
