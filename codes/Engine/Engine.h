/******************************************************************************/
/*!
\file   engine.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2018/11/29

Main engine header file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/


#pragma once
#include "System.h"
#include <conio.h>
#include <io.h>
#include "Input.h"
#include "Windows.h"
#include <stdio.h>
#include <vector>
#include "string"
namespace TE {


	//The engine manage all systems in the game, updating them, routing msgs,
	//and destroy the systems when the game ends
	class Engine
	{
	public:
		Engine();
		~Engine();

		//update all systems
		void GameLoop();
		//Destroy all systems in the engine in reverse to aovid dependency issue
		void DestroyAllsystems();
		//Add systems to the engine
		void AddSystem(Systems * system);
		//Initialize Engine which means initialize all systems
		void Initialize();
		void Filenameloading(void);
		bool GetGameStateIsOn(void) { return GameIsRunning; }
		int countFile(char* Path);
		BOOL IsWow64();
		void Quit();
		float HowMuchTimePassedInGame = 0;
		//Todo : System Message functions
		std::vector<std::string> mVsLevelnamelist;
		std::vector<std::string> mVsTexturenamelist;
		std::vector<std::string> mVsLognamelist;
		std::vector<std::string> mVsSoundnamelist;
		std::vector<std::string> mVsArchtypenamelist;
		bool GameIsRunning;
		bool IsLoggingOn= false;
	private:
		//Track all systems the engine uses
		std::vector<Systems*> SystemList;
		//Main Loop
	
		//delta for each frame
		float dt;
		//fixed time step used for the physics integration function.
		const float pm_fixeddt;
		//Accumlation of the time
		float pm_accumulator;
		//Accumlation of time cannot exceed pm_accmlock;
		const float pm_accumulock;

	};
	//A global pointer ot the instanfce of the engine
	extern Engine* ENGINE;


}// namespace TE End