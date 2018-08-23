/******************************************************************************/
/*!
\file	splash.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Splash state for the game
There is a digipen logo, and if any key is triggered , going to next state
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "splash.h"
#include <stdio.h>
#include "Object.h"
#include "Factory.h"
#include "Input.h"
#include "StateManager.h"
#include "Engine.h"
#include  "LevelManager.h"
#include  <string>
#include "Application.h"
#include "SoundManager.h"
#include "InGameLogic.h"
#include "Archetype.h"
using namespace TE;
float Timer2 = 0;
float angle = 0;
SOUNDID blackholesplash;
splash::splash()
{

}

splash::~splash()
{
}

void splash::Load()
{
	blackholesplash = SOUNDMANAGER->LoadSound("splash.mp3");
	printf("splashLoad\n");
}

void splash::Init()
{
//#ifndef _DEBUG
//	APP->toggle_fullscreen(APP->getWindow(), true);
//#endif
	
	
	//CAMERA->view.RotateZ(TUMath::DegreeToRadian(0.f));
	CAMERA->Initialize();
	std::string path2 = "splash.json";
	SOUNDMANAGER->PlaySounds(blackholesplash, false);

	LEVELMANAGER->LoadLevel(path2);
	camActSplash.cameraSetting(CameraPosType::EN_Splash);

	printf("splashInit\n");
	APP->ResizeAllObjects();

	FACTORY->ObjectIDMap[1]->GetComponent<Transform>()->scale.y = 163;
	FACTORY->ObjectIDMap[2]->GetComponent<Transform>()->scale.y = 470;
	FACTORY->ObjectIDMap[3]->GetComponent<Transform>()->scale.y = 600;


}

void splash::Update(float dt)
{
	dt = dt;
	//CAMERA->lookat(Vector3(0, 0, 3), Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f));

	Timer2 += 5;
	if (Input::IsAnyTriggered())
		STATEMANAGER->Next();

	camActSplash.Update(dt);
	if(CAMERA->cameraPos.x <= 2560 && Timer2 >= 200)
		camActSplash.moveCameraPos(glm::vec3(10.5, 0, 0));
	
	if (CAMERA->cameraPos.x >= 2560)
	{
		STATEMANAGER->Next();

	}
	//}


}

void splash::Free(void)
{
//	delete INGAMELOGIC;
	printf("splashFree\n");
//	INGAMELOGIC->InGameShutdown();
}



void splash::Unload()
{
	printf("splashUnload\n");
}