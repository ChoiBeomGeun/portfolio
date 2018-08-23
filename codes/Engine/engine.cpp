/******************************************************************************/
/*!
\file   engine.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2018/11/29

Main engine source file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/


#pragma  once
#pragma comment(lib, "winmm.lib") 
#include "Engine.h"
#include "DebugUtil.h"
#include "Application.h"
#include <cassert>
#include "Timer.h"
#include "Input.h"
#include "Graphics.h"
#include "Object.h"
#include <iostream>

//#include "Transform.h"
#include "Factory.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "LevelManager.h"
#include "ParticleManager.h"

#include "..\..\example\examples\logging.h"
#include "Physics.h"
#include <windows.h>
#define ISLOGGINGON false;
typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;


using namespace TE;
namespace TE {

	//Global Pointer to the Engine

	Engine * ENGINE = nullptr;

}

Engine::Engine() : GameIsRunning(true), dt(0), pm_fixeddt(1 / 60.f), pm_accumulator(0.f), pm_accumulock(0.25f)
{
	DEBUG_ASSERT(ENGINE != nullptr, "More than 1 instance of the Engine cannot be created !! You Fool!");
	//assert(ENGINE == nullptr, "!!!");
	ENGINE = this;

}

Engine::~Engine()
{
	mVsArchtypenamelist.clear();
	mVsLevelnamelist.clear();
	mVsLognamelist.clear();
	mVsSoundnamelist.clear();
	mVsTexturenamelist.clear();
	//does nothing
}

void Engine::Initialize()
{
	IsLoggingOn = ISLOGGINGON;
	Input::Initialize();
	// Add systems to Engine
	AddSystem(new Application());
	//Add systems to graphics
	AddSystem(new GameLogic());
	AddSystem(new ObjectFactory());
	AddSystem(new Physics());
	AddSystem(new ParticleManager());

	AddSystem(new Graphics());



	AddSystem(new SoundManager());
	AddSystem(new StateManager());

	Filenameloading();

	//  Initialize systems after being added
	for (auto sys : SystemList)
		sys->Initialize();
	//for (unsigned i = 0; i < SystemList.size(); ++i)
	//		SystemList[i]->Update(dt);


}


void Engine::Quit()
{
	GameIsRunning = false;
}
//This is where all systems update
void Engine::GameLoop()
{

	
	//Initialize Timer
	Timer::Initialize();

	DWORD FPS = 60;

	DWORD dwInterval = 1000 / FPS;
	DWORD dwNextTick = 0; //다음 번 루프 순회가 시작 되어야 하는 시간 
	while (GameIsRunning)
	{

		if (dwNextTick > GetTickCount())
			Sleep(dwNextTick - GetTickCount());//dwNextTick - GetTickCount() : 현재의 FPS가 너무 높게 나와 이번 루프에서 지연 되어야 하는 시간

		float frametime = Timer::GetDelta();




		for (unsigned int i = 0; i < SystemList.size(); ++i) {



			SystemList[i]->Update(0.015f);


			if (!GameIsRunning)

				break;
		}
		dwNextTick = GetTickCount() + dwInterval;
	}




	//Todo : Delete all game objects
	FACTORY->DestroyAllObjects();
}

void Engine::AddSystem(Systems * system)
{
	//Add a system to the engine to be updated every frame

	SystemList.push_back(system);


}

void Engine::DestroyAllsystems()
{

	//Delete all Systems ( in reverse) that they were added in
	// to minimize dependency problems between systems

	for (unsigned i = 0; i < SystemList.size(); ++i)
	{
		delete SystemList[SystemList.size() - 1 - i];

	}

}

BOOL Engine::IsWow64()
{
	BOOL bIsWow64 = FALSE;

	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "IsWow64Process");

	if (fnIsWow64Process != NULL)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{
			// handle error
		}
	}

	return bIsWow64;
}


void Engine::Filenameloading(void)
{
	mVsArchtypenamelist.clear();
	mVsLevelnamelist.clear();
	mVsLognamelist.clear();
	mVsSoundnamelist.clear();
	mVsTexturenamelist.clear();
	std::string path;
	char * Userinfo;
	size_t len = 100;
	_dupenv_s(&Userinfo, &len, "USERPROFILE");
	path = Userinfo;
	free(Userinfo);

	_finddata_t level32;
	_finddata_t texture32;
	_finddata_t log32;
	_finddata_t sound32;
	_finddata_t archtype32;
	long levelhandle;
	long texturehandle;
	long loghandle;
	long soundhandle;
	long archtypehandle;

	intptr_t archtypehandle64;
	intptr_t soundhandle64;
	intptr_t loghandle64;
	intptr_t texturehandle64;
	intptr_t levelhandle64;
	__finddata64_t archtype64;
	__finddata64_t sound64;
	__finddata64_t log64;
	__finddata64_t texture64;
	__finddata64_t level64;
	int result = 1;
	int result2 = 1;
	int result3 = 1;
	int result4 = 1;
	int result5 = 1;
	//

	levelhandle = (long)_findfirst(".\\levels.\\*.json", &level32);
	levelhandle64 = (intptr_t)_findfirst64(".\\levels.\\*.json", &level64);

	texturehandle = (long)_findfirst(".\\texture.\\*.png", &texture32);
	texturehandle64 = (intptr_t)_findfirst64(".\\texture.\\*.png", &texture64);

	loghandle = (long)_findfirst(".\\logging.\\*.json", &log32);
	loghandle64 = (intptr_t)_findfirst64(".\\logging.\\*.json", &log64);


	soundhandle = (long)_findfirst(".\\sounds.\\*.mp3", &sound32);
	soundhandle64 = (intptr_t)_findfirst64(".\\sounds.\\*.mp3", &sound64);

	archtypehandle = (long)_findfirst(".\\Archtypes.\\*.json", &archtype32);
	archtypehandle64 = (intptr_t)_findfirst64(".\\Archtypes.\\*.json", &archtype64);



	if (levelhandle == -1 || levelhandle64 == -1)
	{
		printf("Level : There were no files.\n");
		return;
	}

	if (texturehandle == -1 || texturehandle64 == -1)
	{
		printf("Texture : There were no files.\n");
		return;
	}


	if (loghandle == -1 || loghandle64 == -1)
	{
		printf("Log : There were no files.\n");
		return;
	}


	if (soundhandle == -1 || soundhandle64 == -1)
	{
		printf("Sound : There were no files.\n");
		return;
	}

	if (archtypehandle == -1 || archtypehandle64 == -1)
	{
		printf("Archtypes : There were no files.\n");
		return;
	}
	while (result != -1)
	{

		if (IsWow64())
			mVsLevelnamelist.push_back(level32.name);
		else
			mVsLevelnamelist.push_back(level64.name);


		if (IsWow64())
		{
			result = _findnext(levelhandle, &level32);

		}
		else
		{
			result = _findnext64(levelhandle64, &level64);
		}

	}

	while (result2 != -1)
	{

		if (IsWow64())
			mVsTexturenamelist.push_back(texture32.name);
		else
			mVsTexturenamelist.push_back(texture64.name);


		if (IsWow64())
		{
			result2 = _findnext(texturehandle, &texture32);

		}
		else
		{
			result2 = _findnexti64(texturehandle64, &texture64);
		}

	}

	while (result3 != -1)
	{

		if (IsWow64())
			mVsLognamelist.push_back(log32.name);
		else
			mVsLognamelist.push_back(log64.name);


		if (IsWow64())
		{
			result3 = _findnext(loghandle, &log32);

		}
		else
		{
			result3 = _findnext64(loghandle64, &log64);
		}

	}

	while (result4 != -1)
	{

		if (IsWow64())
			mVsSoundnamelist.push_back(sound32.name);
		else
			mVsSoundnamelist.push_back(sound64.name);


		if (IsWow64())
		{
			result4 = _findnext(soundhandle, &sound32);

		}
		else
		{
			result4 = _findnext64(soundhandle64, &sound64);
		}

	}

	while (result5 != -1)
	{

		if (IsWow64())
			mVsArchtypenamelist.push_back(archtype32.name);
		else
			mVsArchtypenamelist.push_back(archtype64.name);


		if (IsWow64())
		{
			result5 = _findnext(archtypehandle, &archtype32);

		}
		else
		{
			result5 = _findnext64(archtypehandle64, &archtype64);
		}

	}
	if (IsWow64()) {
		_findclose(levelhandle);
		_findclose(texturehandle);
		_findclose(loghandle);
		_findclose(soundhandle);
		_findclose(archtypehandle);
	}
	else {
		_findclose(levelhandle64);
		_findclose(texturehandle64);
		_findclose(loghandle64);
		_findclose(soundhandle64);
		_findclose(archtypehandle64);
	}


}