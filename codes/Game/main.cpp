/******************************************************************************/
/*!
\file	main.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Whole main game loop for the game
In this cpp, there should be add states and set states
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include "StateManager.h"
#include "Menu.h"
#include "SDL.h"
#include "TE.h"
#include "Engine.h"
#include "Option.h"
#include  "Level1.h"
#include "splash.h"
#include "Pause.h"
#include "LevelSelect.h"
#include "StateLists.h"
#include "logging.h"
#include <crtdbg.h>
#include "LevelManager.h"
#include "MapEditor.h"
#include "InGameLogic.h"
#include "Clearzone.h"
#include "LoseconditionLogic.h"
#include "Trigger.h"
#include "cAutoMoving.h"
#include "Automoving.h"
#include "Intro.h"
#include "Ending.h"
using namespace TE;
int main(int,char**)
{
	
 	DEBUG_MEMORY_LEAK_CHECKS();
	//Menu Menu;

	
	DEBUG_CREATE_CONSOLE();
	Engine * TEengine = new Engine();

	//Todo : Create Engine
	 
	//Todo : Initialize the Engine and initialize all systems.
	TEengine->Initialize();
	//Todo : Create initial game state, main menu 

	INGAMELOGIC = new InGameLogic;
	INGAMELOGIC->InGameLogicAdd(new TriggerLogic());
	INGAMELOGIC->InGameLogicAdd(new ClearzoneLogic());
	INGAMELOGIC->InGameLogicAdd(new LoseconditionLogic());

	STATEMANAGER->AddState(new splash);
	STATEMANAGER->AddState(new Menu);
	STATEMANAGER->AddState(new Option);
	STATEMANAGER->AddState(new LevelSelect);
	STATEMANAGER->AddState(new Level1);
	STATEMANAGER->AddState(new Pause);

	STATEMANAGER->AddState(new MapEditor);
	STATEMANAGER->AddState(new Intro);
	STATEMANAGER->AddState(new Ending);
	STATEMANAGER->SetPauseState(StatesList::Pause);
	STATEMANAGER->SetStartState(StatesList::Intro);


	//Todo : Main Loop
	TEengine->GameLoop();
	INGAMELOGIC->DestoryAllGameLogics();
	delete INGAMELOGIC;
	//Todo : Shutdown the engine
	//Also means shutdown and clean all systems
	STATEMANAGER->DestoryAllStates();
	TEengine->DestroyAllsystems();

			
		delete LOGGINGSYSTEM;
	//Todo : Delete the Engine


	SDL_Delay(2000);
	DEBUG_DESTORY_CONSOLE();
	
	delete TEengine;
	
	return 0;
}