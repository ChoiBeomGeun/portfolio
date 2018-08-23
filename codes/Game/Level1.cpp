/******************************************************************************/
/*!
\file	level1.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

All levels is running in this state
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Level1.h"
#include <stdio.h>
#include "Object.h"
#include "Factory.h"
#include "Input.h"
#include "StateManager.h"
#include "Engine.h"
#include "Graphics.h"
#include  "LevelManager.h"
#include  "Timer.h"
#include "Application.h"
#include "SoundManager.h"
#include "Archetype.h"
#include "InGameLogic.h"
#include "Trigger.h"
#include "System.h"
#include "logging.h"
#include "Clearzone.h"
#include "StateLists.h"
#include "ReplayLogic.h"
#include "CameraMovement.h"
#include "Transform.h"
#include <random>
#include "PlayerController.h"
#include "cAutoMoving.h"
#include "Automoving.h"
#include "LoseconditionLogic.h"
#define LOGGINGSTART false

using namespace TE;
void MakingInstructions(float dt);
void CheatKeyFunctions(void);
static int i = 0;
static int j = 0;
float dangle = 0;
int replay = 0;
extern int i_angleOfspace;
bool IsAutoplay = false;
std::vector<glm::vec3> replayPos;
std::vector<Object> replayPlayer;
bool LosesoundOnetime = true;
bool IndicatorCheck = true;
bool GodMode = false;
std::string  path2;
Object * HUDLevelname;
Object * Backgroundobj[11];
Object * Indicator;
Object * Indicator1;
Object * Indicator2;
unsigned int Background;
unsigned int loseSound;
unsigned int loseFallingSound;
unsigned int loseElecSound;
unsigned int winSound2;
Jsonclass file;
Json::Value root;
Object * player;
bool LoseSOUNDONCE = true;
Object * Movingtest;

Object * laser_particle;
Object * trail_particle;
Level1::Level1()
{
}

Level1::~Level1()
{
}

void Level1::Load()
{

}

void Level1::Init()
{
	CAMERA->Initialize();

	LosesoundOnetime = true;
	
	path2 = "SAVE";
	_camPaceSpeed = 100.0f;

	moving = false;
	
	std::string saveLevel = path2;

	path2 = ".\\autoplays.\\" + path2;


	file.ReadFile(path2);

	camAct.Setshakeduration(2);
	loseSound = SOUNDMANAGER->LoadSound("lose.mp3");
	loseFallingSound = SOUNDMANAGER->LoadSound("fall.mp3");
	loseElecSound = SOUNDMANAGER->LoadSound("elec.mp3");
	Background = SOUNDMANAGER->LoadSound("menu.mp3");
	STATEMANAGER->b_IsRot90 = false;
	STATEMANAGER->b_IsRot180 = false;
	STATEMANAGER->b_IsGameLevel = true;
	STATEMANAGER->b_IsReplayStart = true;
	STATEMANAGER->b_IsReplay = false;
	STATEMANAGER->b_Relplay = false;
	STATEMANAGER->b_IsDelay = false;
	STATEMANAGER->AniSave.clear();
	APP->b_Win = false;
	APP->b_Lose = false;

	LEVELMANAGER->LoadLevel(STATEMANAGER->Loadtolevelname);

	
 	std::string levelname = std::to_string(STATEMANAGER->i_LevelSelect) + ".png";
	HUDLevelname = FACTORY->CreateHUD(glm::vec3(0, 0.5, 0), glm::vec3(0.1, 0.2, 0));
	HUDLevelname->GetComponent<Transform>()->scale = glm::vec3(50, 50, 0);
	HUDLevelname->GetComponent<Transform>()->position.y = HUDLevelname->GetComponent<Transform>()->position.y - HUDLevelname->GetComponent<Transform>()->scale.y;
	HUDLevelname->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id(levelname);
	HUDLevelname->objectstyle = Objectstyle::Button;



	INGAMELOGIC->InGameInit();
	SOUNDMANAGER->PlaySounds(Background, true);
	FACTORY->GetPlayer()->GetComponent<Body>()->GroundType = Grounded::Ground;
	player = FACTORY->GetPlayer();
	STATEMANAGER->InitplayerPos = player->GetComponent<Transform>()->GetPosition();
	player->GetComponent<Animation>()->setFrame(.2f);
	player->GetComponent<Animation>()->setTime(.2f);
	player->GetComponent<Animation>()->_limit_frame = 0.8f;
	_camPaceSpeed = 5.0f;
	_camPacedirction = CAMERA->cameraPos - player->GetComponent<Transform>()->position;
	_camStartPosition = glm::vec3{ 0.f, 0.f, 0.f };

	CAMERA->IsCameraAttached = true;
	CAMERA->cameraUp.x = 0;
	CAMERA->cameraUp.y = 1;


	camAct.cameraOriginPos = CAMERA->cameraPos;
	CAMERA->CenterOfCamera.x = FACTORY->LeftBoundary()->GetComponent<Transform>()->position.x + (FACTORY->RightBoundary()->GetComponent<Transform>()->position.x - FACTORY->LeftBoundary()->GetComponent<Transform>()->position.x) *.5f;
	CAMERA->CenterOfCamera.y = FACTORY->DownBoundary()->GetComponent<Transform>()->position.y + (FACTORY->UpBoundary()->GetComponent<Transform>()->position.y - FACTORY->DownBoundary()->GetComponent<Transform>()->position.y)*.5f;
	glm::vec2(CAMERA->cameraPos) = CAMERA->CenterOfCamera;
	STATEMANAGER->IsDrawing = false;
	
	

	static float loadingtimer = 0.1f;
	APP->IsKeyBoardAvailable = false;
  	while (loadingtimer >0)
	{

		loadingtimer -= Timer::GetDelta();
	

	}

	Input::Reset();

	loadingtimer = 0.1f;

	camAct.cameraSetting(EN_playerPos);


	loadbackground();

	trail_particle = FACTORY->CreateHUD(glm::vec3(0), glm::vec3(0));
	trail_particle->GetComponent<Sprite>()->isPerspective = true;
	PARTICLEMANAGER->LoadEmitter(trail_particle, "PlayerTrail.json");



	for (auto p : PARTICLEMANAGER->m_EmitterList)
	{
		p->isOn = true;
		if (p->type == ET_EXPLOSION)
		{
			p->isOn = false;
			p->pos = FACTORY->GetClearZone()->GetComponent<Transform>()->position;
		}
		else if(p->type == ET_TRAIL)
		{
			p->pos = player->GetComponent<Transform>()->position;
		}
	
	}
	LoseSOUNDONCE = true;
}

void Level1::Update(float dt)
{

	
	APP->IsKeyBoardAvailable = true;
	camAct.Update(dt);

	CheatKeyFunctions();


	if (APP->b_Lose)
	{
		if(LOSECONDITIONLOGIC->IsBoxDie)
		SOUNDMANAGER->PlayOnceSounds(loseSound, false, LoseSOUNDONCE);
		if (LOSECONDITIONLOGIC->IsFalling)
			SOUNDMANAGER->PlayOnceSounds(loseFallingSound, false, LoseSOUNDONCE);
		if (LOSECONDITIONLOGIC->IsElec)
			SOUNDMANAGER->PlayOnceSounds(loseElecSound, false, LoseSOUNDONCE);
		LoseSOUNDONCE = false;
	}

	if (STATEMANAGER->Loadtolevelname == "stairlevel.json")
	{
		FACTORY->ObjectIDMap[4]->GetComponent<Sprite>()->Color[4] = 0;
		FACTORY->ObjectIDMap[9]->GetComponent<Sprite>()->Color[4] = 0;
		FACTORY->ObjectIDMap[10]->GetComponent<Sprite>()->Color[4] = 0;
		FACTORY->ObjectIDMap[17]->GetComponent<Sprite>()->Color[4] = 0;
	}


	if (Input::IsTriggered(SDL_SCANCODE_R) && !STATEMANAGER->b_IsReplay && !APP->b_Win && !APP->b_Lose)
		STATEMANAGER->Restart();
	if (STATEMANAGER->b_IsReplayStart) {
		ReplayerInfo temp;
		temp.Pos = player->GetComponent<Transform>()->GetPosition();
		temp.aniframe = player->GetComponent<Animation>()->getFrame();
		temp.anitime = player->GetComponent<Animation>()->getTime();
		temp.mouseinfo = player->GetComponent<Animation>()->isFlippedX();
		STATEMANAGER->Replayerinfo.push(temp);
	}
	MakingInstructions(dt);

	if (!ENGINE->GetGameStateIsOn())
	{

		delete INGAMELOGIC;
		delete LOGGINGSYSTEM;
	}

	if (IsAutoplay)
	{
		float Xpos = file.mRoot["PositionX"][j].asFloat();
		float Ypos = file.mRoot["PositionY"][j].asFloat();
		float Frame = file.mRoot["Frame"][j].asFloat();
		float FrameTime = file.mRoot["FrameTime"][j].asFloat();
		bool Pressed = file.mRoot["isFlippedX"][j].asBool();
		FACTORY->GetPlayer()->GetComponent<Transform>()->SetPosition(glm::vec3(Xpos, Ypos, 0));
		FACTORY->GetPlayer()->GetComponent<Animation>()->setFrame(Frame);
		FACTORY->GetPlayer()->GetComponent<Animation>()->setTime(FrameTime);
		FACTORY->GetPlayer()->GetComponent<Animation>()->setFlipX(Pressed);
		j++;
	}
	if (!STATEMANAGER->b_IsReplay)
	{
		for (int i = 0; i < 11; ++i)
		{
			if (STATEMANAGER->b_IsRot90) {
				Backgroundobj[i]->GetComponent<Transform>()->angle += 2.25;
			}
			else if (STATEMANAGER->b_IsRot180)
			{
				Backgroundobj[i]->GetComponent<Transform>()->angle -= 2.25;

			}
		}
	}

	
	INGAMELOGIC->InGameUpdate(dt);
	if (STATEMANAGER->b_IsReplay)
	{
		APP->b_Win = false;
	}


	if (APP->b_Lose)
	{
	
		CAMERA->IsCameraShaking = LOSECONDITIONLOGIC->isBoundaryLose ? false : true;
	}

	if (CAMERA->IsCameraShaking)
	{
	
		camAct.cameraOriginPos = CAMERA->cameraPos;
		camAct.ShakeCamera(dt);
	}

	if (STATEMANAGER->b_IsReplay)
	{
		camAct.Update(dt);
		static bool first = true;
		if (STATEMANAGER->ReplayInit)
		{
			MakeReplayerUI();
			TRIGGERLOGIC->Initialize();
			CAMERA->cameraUp.x = 0;
			CAMERA->cameraUp.y = 1;
			PHYSICS->gravityScale = -20.f;
			PHYSICS->GravityType = Gravity::y_Minus;
			PHYSICS->gravity = glm::vec3(0, PHYSICS->gravityScale, 0);
		}		
		first = false;
		SetReplayer();
	}

	if (APP->b_Win)
	{
		STATEMANAGER->b_IsReplayStart = false;
		for (auto p : PARTICLEMANAGER->m_EmitterList)
		{

			if (p->type == ET_EXPLOSION)
			{
				if (!p->isOn)
					PARTICLEMANAGER->initialize_life_time();
				p->isOn = true;
			}
		}
		
		STATEMANAGER->b_IsDelay =	INGAMELOGIC->InGameDelay(dt, 3);
		if(!STATEMANAGER->b_IsDelay)
		{
			for (auto p : PARTICLEMANAGER->m_EmitterList)
			{

				if (p->type == ET_EXPLOSION)
				{
					p->isOn = false;
				}
			}

			STATEMANAGER->b_IsReplayStart = false;
			STATEMANAGER->b_IsReplay = true;
			STATEMANAGER->b_IsDelay = false;
		}
	}
	if (!PARTICLEMANAGER->m_EmitterList.empty() && FACTORY->GetPlayer() != nullptr)
	{
		for (auto p : PARTICLEMANAGER->m_EmitterList)
		{
			if (p->type == ET_TRAIL)
				p->pos = FACTORY->GetPlayer()->GetComponent<Transform>()->position;
			else if (p->type == ET_EXPLOSION)
				p->pos = FACTORY->GetClearZone()->GetComponent<Transform>()->position;
			
		}
	}


}

void Level1::Free(void)
{
	Input::Reset();


	while (!STATEMANAGER->Replayerinfo.empty())
		STATEMANAGER->Replayerinfo.pop();
	
	CAMERA->IsCameraShaking = false;
	STATEMANAGER->b_IsAutoplaying = false;
	IsAutoplay = false;
	j = 0;

	LOGGINGSYSTEM->SavingLog();
	STATEMANAGER->b_IsGameLevel = false;
 	CAMERA->cameraUp.x = 0;
	CAMERA->cameraUp.y = 1;
	PHYSICS->gravityScale = -20.f;
	PHYSICS->GravityType = Gravity::y_Minus;
	PHYSICS->gravity = glm::vec3(0, PHYSICS->gravityScale, 0);
	STATEMANAGER->b_IsReplayStart = true;
	STATEMANAGER->b_IsReplay = false;
	STATEMANAGER->b_Relplay = false;
	INGAMELOGIC->InGameShutdown();
	PARTICLEMANAGER->Delete_all_particles();
	FACTORY->DestroyAllObjects();

	
}
void Level1::Unload()
{
	for (auto p : PARTICLEMANAGER->m_EmitterList)
	{
		if (p->type == ET_EXPLOSION)
		{
			p->isOn = false;
		}
	}
	STATEMANAGER->b_IsReplayStart = false;
	STATEMANAGER->b_IsReplay = false;
	STATEMANAGER->b_IsDelay = false;
}

void Level1::loadbackground()
{
	float background_trsparent  = 140.f;
	// top right
	Backgroundobj[0] = FACTORY->CreateHUD(glm::vec3(.38, .5, 0), glm::vec3(.1, .1, 0));
	Backgroundobj[0]->GetComponent<Transform>()->position = glm::vec3(  Backgroundobj[0]->GetComponent<Transform>()->position.x, Backgroundobj[0]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[0]->GetComponent<Transform>()->scale.y = Backgroundobj[0]->GetComponent<Transform>()->scale.x;
	Backgroundobj[0]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("sawtooth1_1.png");
	Backgroundobj[0]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[0]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[0]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);

	Backgroundobj[1] = FACTORY->CreateHUD(glm::vec3(.495, .45, 0), glm::vec3(.12, .12, 0));
	Backgroundobj[1]->GetComponent<Transform>()->position = glm::vec3(Backgroundobj[1]->GetComponent<Transform>()->position.x, Backgroundobj[1]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[1]->GetComponent<Transform>()->scale.y = Backgroundobj[1]->GetComponent<Transform>()->scale.x;
	Backgroundobj[1]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("sawtooth1_2.png");
	Backgroundobj[1]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[1]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[1]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);

	Backgroundobj[2] = FACTORY->CreateHUD(glm::vec3(.4, .315, 0), glm::vec3(.105, .105, 0));
	Backgroundobj[2]->GetComponent<Transform>()->scale.y = Backgroundobj[2]->GetComponent<Transform>()->scale.x;
	Backgroundobj[2]->GetComponent<Transform>()->position = glm::vec3(Backgroundobj[2]->GetComponent<Transform>()->position.x, Backgroundobj[2]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[2]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("sawtooth1_3.png");
	Backgroundobj[2]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[2]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[2]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);
	// top right

	// bot right
	Backgroundobj[3] = FACTORY->CreateHUD(glm::vec3(.515, .5, 0), glm::vec3(.135, .135, 0));
	Backgroundobj[3]->GetComponent<Transform>()->scale.y = Backgroundobj[3]->GetComponent<Transform>()->scale.x;
	Backgroundobj[3]->GetComponent<Transform>()->position = glm::vec3(Backgroundobj[3]->GetComponent<Transform>()->position.x,  -Backgroundobj[3]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[3]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("sawtooth2_1.png");
	Backgroundobj[3]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[3]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[3]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);

	Backgroundobj[4] = FACTORY->CreateHUD(glm::vec3(.405, .405, 0), glm::vec3(.095, .095, 0));
	Backgroundobj[4]->GetComponent<Transform>()->scale.y = Backgroundobj[4]->GetComponent<Transform>()->scale.x;
	Backgroundobj[4]->GetComponent<Transform>()->position = glm::vec3(Backgroundobj[4]->GetComponent<Transform>()->position.x, -Backgroundobj[4]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[4]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("sawtooth2_2.png");
	Backgroundobj[4]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[4]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[4]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);
	// bot right

	// top left
	Backgroundobj[5] = FACTORY->CreateHUD(glm::vec3(.5, .5, 0), glm::vec3(.1, .1, 0));
	Backgroundobj[5]->GetComponent<Transform>()->scale.y = Backgroundobj[5]->GetComponent<Transform>()->scale.x;
	Backgroundobj[5]->GetComponent<Transform>()->position = glm::vec3(-Backgroundobj[5]->GetComponent<Transform>()->position.x, Backgroundobj[5]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[5]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("bigsawtooth.png");
	Backgroundobj[5]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[5]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[5]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);

	Backgroundobj[6] = FACTORY->CreateHUD(glm::vec3(.385, .475, 0), glm::vec3(.109, .109, 0));
	Backgroundobj[6]->GetComponent<Transform>()->scale.y = Backgroundobj[6]->GetComponent<Transform>()->scale.x;
	Backgroundobj[6]->GetComponent<Transform>()->position = glm::vec3(-Backgroundobj[6]->GetComponent<Transform>()->position.x, Backgroundobj[6]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[6]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("sawtooth2_1.png");
	Backgroundobj[6]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[6]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[6]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);

	Backgroundobj[7] = FACTORY->CreateHUD(glm::vec3(.45, .325, 0), glm::vec3(.095, .095, 0));
	Backgroundobj[7]->GetComponent<Transform>()->scale.y = Backgroundobj[7]->GetComponent<Transform>()->scale.x;
	Backgroundobj[7]->GetComponent<Transform>()->position = glm::vec3(-Backgroundobj[7]->GetComponent<Transform>()->position.x, Backgroundobj[7]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[7]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("boundsawtooth1_1.png");
	Backgroundobj[7]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[7]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[7]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);
	// top left

	// bot left
	Backgroundobj[8] = FACTORY->CreateHUD(glm::vec3(.5, .5, 0), glm::vec3(.115, .115, 0));
	Backgroundobj[8]->GetComponent<Transform>()->scale.y = Backgroundobj[8]->GetComponent<Transform>()->scale.x;
	Backgroundobj[8]->GetComponent<Transform>()->position = glm::vec3(-Backgroundobj[8]->GetComponent<Transform>()->position.x, -Backgroundobj[8]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[8]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("bigsawtooth.png");
	Backgroundobj[8]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[8]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[8]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);

	Backgroundobj[9] = FACTORY->CreateHUD(glm::vec3(.5, .3, 0), glm::vec3(.095, .095, 0));
	Backgroundobj[9]->GetComponent<Transform>()->scale.y = Backgroundobj[9]->GetComponent<Transform>()->scale.x;
	Backgroundobj[9]->GetComponent<Transform>()->position = glm::vec3(-Backgroundobj[9]->GetComponent<Transform>()->position.x, -Backgroundobj[9]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[9]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("sawtooth1_1.png");
	Backgroundobj[9]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[9]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[9]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);

	Backgroundobj[10] = FACTORY->CreateHUD(glm::vec3(.4, .4, 0), glm::vec3(.1, .1, 0));
	Backgroundobj[10]->GetComponent<Transform>()->scale.y = Backgroundobj[10]->GetComponent<Transform>()->scale.x;
	Backgroundobj[10]->GetComponent<Transform>()->position = glm::vec3(-Backgroundobj[10]->GetComponent<Transform>()->position.x, -Backgroundobj[10]->GetComponent<Transform>()->position.y, 0);
	Backgroundobj[10]->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("boundsawtooth1_1.png");
	Backgroundobj[10]->objectstyle = Objectstyle::BackGround;
	Backgroundobj[10]->GetComponent<Sprite>()->depth = -1;
	Backgroundobj[10]->GetComponent<Sprite>()->ChangeColor(255, 255, 255, background_trsparent);
	// bot left

	for (int i = 0; i<11; ++i)
	{
		Backgroundobj[i]->GetComponent<Sprite>()->isRotating = true;
	}
}


void CheatKeyFunctions(void) {





	if (Input::IsTriggered(SDL_SCANCODE_F8) && STATEMANAGER->i_LevelSelect != 20 && !STATEMANAGER->b_IsRot180 && !STATEMANAGER->b_IsRot90)
	{

		CAMERA->cameraUp.x = 0;
		CAMERA->cameraUp.y = 1;
	
		STATEMANAGER->AniSave.clear();
		std::string level = "level";
		level += std::to_string(++STATEMANAGER->i_LevelSelect);
		level += +".json";
		STATEMANAGER->Loadtolevelname = level;
		STATEMANAGER->b_IsReplay = false;
		STATEMANAGER->b_Relplay = false;
		STATEMANAGER->b_IsPauseFirst = true;
		STATEMANAGER->Restart();



	}
	if (Input::IsTriggered(SDL_SCANCODE_F7))
		STATEMANAGER->Restart();


}



void MakingInstructions(float dt) 
{

	static float timeringame = 2;


	timeringame -= dt;
	if (IndicatorCheck &&timeringame <= 0 && STATEMANAGER->Loadtolevelname == "level1.json")
	{

		Indicator = FACTORY->CreateArchetype(ReadingArchetype("Button.json"));
		Indicator->GetComponent<Transform>()->SetPosition(glm::vec3(FACTORY->GetPlayer()->GetComponent<Transform>()->position.x - 80, 130 + FACTORY->GetPlayer()->GetComponent<Transform>()->position.y, FACTORY->GetPlayer()->GetComponent<Transform>()->position.z));
		Indicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("left.png");
		Indicator->GetComponent<Transform>()->scale.x = 80;
		Indicator->GetComponent<Transform>()->scale.y = 80;

		Indicator1 = FACTORY->CreateArchetype(ReadingArchetype("Button.json"));
		Indicator1->GetComponent<Transform>()->SetPosition(glm::vec3(FACTORY->GetPlayer()->GetComponent<Transform>()->position.x + 80, 130 + FACTORY->GetPlayer()->GetComponent<Transform>()->position.y, FACTORY->GetPlayer()->GetComponent<Transform>()->position.z));
		Indicator1->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("right.png");
		Indicator1->GetComponent<Transform>()->scale.x = 80;
		Indicator1->GetComponent<Transform>()->scale.y = 80;

		Indicator2 = FACTORY->CreateArchetype(ReadingArchetype("Button.json"));
		Indicator2->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("space.png");
		Indicator2->GetComponent<Transform>()->SetPosition(glm::vec3(FACTORY->GetPlayer()->GetComponent<Transform>()->position.x, 210 + FACTORY->GetPlayer()->GetComponent<Transform>()->position.y, FACTORY->GetPlayer()->GetComponent<Transform>()->position.z));
		Indicator2->GetComponent<Transform>()->scale.x = 210;
		Indicator2->GetComponent<Transform>()->scale.y = 80;
		IndicatorCheck = false;
	}




}