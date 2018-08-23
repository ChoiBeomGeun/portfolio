/******************************************************************************/
/*!
\file	ReplayLogic.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

ReplayLogic implementation
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "ReplayLogic.h" 
#include "StateManager.h"
#include "Factory.h"
#include "Object.h"
#include "Input.h"
#include "SoundManager.h"
#include "LevelManager.h"
#include "Level1.h"
#include "Trigger.h"
#include "ParticleManager.h"
#include "CameraMovement.h"
#include "Clearzone.h"
#include "StateLists.h"
using namespace TE;
unsigned int index = 0;
void ButtonLogic(void);
void ReStartgame3(void);
void LevelSelect3(void);
void Backgame3(void);
void(*pausefunction3[3])(void) = { Backgame3,ReStartgame3,LevelSelect3 };
glm::vec3 Vec3Buttonscale3 = glm::vec3(.10f, .15f, 0);
int pauseindex3 = 0;
glm::vec3 Vec3buttonPostion3 = glm::vec3(.35f, 0, 0);
unsigned int rlmove;
unsigned int rlselect;
unsigned int rlback;
unsigned int rlwin;
bool SettingItor = false;
Object * replayer;
Object * oReBackbutton;
Object * oReRestartbutton;
Object * oReLevelbutton;
Object * ReeplayImage;
Object * ReeplayUI;

TE::CameraAction replayCam;
std::queue<ReplayerInfo> itor;
static bool IsButtonAvailable = true;

void ReStartgame3(void)
{
	
	while (!STATEMANAGER->Replayerinfo.empty())
		STATEMANAGER->Replayerinfo.pop();
	FreeReplayer();
	STATEMANAGER->Restart();
	PARTICLEMANAGER->Initialize();
}

void LevelSelect3(void)
{
	FreeReplayer();
	STATEMANAGER->b_IsReplay = false;
	STATEMANAGER->b_Relplay = false;
	STATEMANAGER->b_IsPauseFirst = true;
	STATEMANAGER->MoveState(3);
	while (!STATEMANAGER->Replayerinfo.empty())
		STATEMANAGER->Replayerinfo.pop();
	PARTICLEMANAGER->Initialize();
}
//Move next
void Backgame3(void)
{
	FreeReplayer();
	if (STATEMANAGER->i_LevelSelect == 20) {
		STATEMANAGER->MoveState(StatesList::Ending);
		return;
	}

	
	CAMERA->cameraUp.x = 0;
	CAMERA->cameraUp.y = 1;

	std::string level = "level";
	level += std::to_string(++STATEMANAGER->i_LevelSelect);
	level += +".json";
	STATEMANAGER->Loadtolevelname = level;
	STATEMANAGER->b_IsReplay = false;
	STATEMANAGER->b_Relplay = false;
	STATEMANAGER->b_IsPauseFirst = true;
	STATEMANAGER->MoveState(4);
	PARTICLEMANAGER->Initialize();
}


void MakeReplayerUI(void) {
	
	STATEMANAGER->b_IsGameLevel = true;
	pauseindex3 = 0;
	SOUNDMANAGER->DeleteSounds();
	FACTORY->DestroyAllObjects();

	

	LEVELMANAGER->LoadLevel(STATEMANAGER->Loadtolevelname);
	Level1::loadbackground();


	oReBackbutton = FACTORY->CreateHUD(glm::vec3(Vec3buttonPostion3.x, Vec3buttonPostion3.y + .200f, 0), Vec3Buttonscale3);
	oReBackbutton->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("nextlevel.png");
	oReRestartbutton = FACTORY->CreateHUD(glm::vec3(Vec3buttonPostion3.x, Vec3buttonPostion3.y, Vec3buttonPostion3.z), Vec3Buttonscale3);
	oReRestartbutton->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("retry.png");
	oReLevelbutton = FACTORY->CreateHUD(glm::vec3(Vec3buttonPostion3.x, Vec3buttonPostion3.y - .200f, Vec3buttonPostion3.z), Vec3Buttonscale3);
	oReLevelbutton->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("levelselect.png");
	ReeplayImage = FACTORY->CreateHUD(glm::vec3(0, 0, Vec3buttonPostion3.z), glm::vec3(1, 1, 0));
	ReeplayImage->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("replay.png");
	replayer = FACTORY->GetPlayer();
	STATEMANAGER->ReplayInit = false;
	TRIGGERLOGIC->Free();
	TRIGGERLOGIC->Initialize();
	IsButtonAvailable = true;
	itor = STATEMANAGER->Replayerinfo;
	rlmove = SOUNDMANAGER->LoadSound("menumove.mp3");
	rlback = SOUNDMANAGER->LoadSound("menuselect.mp3");
	rlselect = SOUNDMANAGER->LoadSound("menuselect.mp3");
	rlwin = SOUNDMANAGER->LoadSound("win3.mp3");
	for (auto p : PARTICLEMANAGER->m_EmitterList)
	{
		p->isOn = true;
		if (p->type == ET_EXPLOSION)
		{
			p->isOn = false;
			p->pos = FACTORY->GetClearZone()->GetComponent<Transform>()->position;
		}
	}
}

void SetReplayer(void) {
	if (!replayer)
		return;

	replayer->GetComponent<Transform>()->SetPosition(itor.front().Pos);
	replayer->GetComponent<Animation>()->setFrame(itor.front().aniframe);
	replayer->GetComponent<Animation>()->setTime(itor.front().anitime);
	replayer->GetComponent<Animation>()->setFlipX(itor.front().mouseinfo);
	for (auto p : PARTICLEMANAGER->m_EmitterList)
	{
		p->isOn = true;
		if (p->type == ET_EXPLOSION)
		{
			p->isOn = false;
			p->pos = FACTORY->GetClearZone()->GetComponent<Transform>()->position;
		}
	}
	itor.pop();
	if (itor.size() <= 0) {
		SOUNDMANAGER->PlaySounds(rlwin, false);
		FACTORY->DestroyAllObjects();
		LEVELMANAGER->LoadLevel(STATEMANAGER->Loadtolevelname);
		Level1::loadbackground();
		TRIGGERLOGIC->Initialize();
		oReBackbutton = FACTORY->CreateHUD(glm::vec3(Vec3buttonPostion3.x, Vec3buttonPostion3.y + .200f, Vec3buttonPostion3.z), Vec3Buttonscale3);
		oReBackbutton->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("nextlevel.png");
		oReRestartbutton = FACTORY->CreateHUD(glm::vec3(Vec3buttonPostion3.x, Vec3buttonPostion3.y, Vec3buttonPostion3.z), Vec3Buttonscale3);
		oReRestartbutton->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("retry.png");
		oReLevelbutton = FACTORY->CreateHUD(glm::vec3(Vec3buttonPostion3.x, Vec3buttonPostion3.y -.200f, Vec3buttonPostion3.z), Vec3Buttonscale3);
		oReLevelbutton->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("levelselect.png");
		ReeplayImage = FACTORY->CreateHUD(glm::vec3(0, 0, Vec3buttonPostion3.z), glm::vec3(1, 1, 0));
		ReeplayImage->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("replay.png");
		replayer = FACTORY->GetPlayer();


		
		CAMERA->cameraUp.x = 0;
		CAMERA->cameraUp.y = 1;
		PHYSICS->gravityScale = -20.f;
		PHYSICS->GravityType = Gravity::y_Minus;
		PHYSICS->gravity = glm::vec3(0, PHYSICS->gravityScale, 0);
		itor = STATEMANAGER->Replayerinfo;
	}


	if (IsButtonAvailable)
		ButtonLogic();
	else
		return;

}

void ButtonLogic(void)
{
	if (Input::IsTriggered(SDL_SCANCODE_DOWN))
		if (pauseindex3 <= 3)
		{
			SOUNDMANAGER->PlaySounds(rlmove, false);
			pauseindex3++;


			if (pauseindex3 == 3)
				pauseindex3 = 0;
		}

	if (Input::IsTriggered(SDL_SCANCODE_UP))
		if (pauseindex3 >= 0)
		{
			SOUNDMANAGER->PlaySounds(rlmove, false);
			pauseindex3--;

			if (pauseindex3 == -1)
			{

				pauseindex3 = 2;
			}
		}


	if ((Input::IsTriggered(SDL_SCANCODE_SPACE) || (Input::IsTriggered(SDL_SCANCODE_RETURN)))
		&& (!STATEMANAGER->b_IsRotating)
		)
	{
		SOUNDMANAGER->PlaySounds(rlselect, false);
		pausefunction3[pauseindex3]();
		return;
	}






	if (oReBackbutton&& oReLevelbutton && oReRestartbutton) {
		switch (pauseindex3)
		{
		case 1:
			oReRestartbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 0, 255);
			oReBackbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);
			oReLevelbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);
			break;
		case 0:
			oReBackbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 0, 255);
			oReRestartbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);
			oReLevelbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);
			break;
		case 2:
			oReLevelbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 0, 255);
			oReRestartbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);
			oReBackbutton->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);
			break;
		}
	}


}

void FreeReplayer(void) {


	FACTORY->Destroy(oReBackbutton);
	FACTORY->Destroy(oReLevelbutton);
	FACTORY->Destroy(oReRestartbutton);
	FACTORY->Destroy(ReeplayImage);
	STATEMANAGER->b_IsReplay = false;
	IsButtonAvailable = false;
	STATEMANAGER->b_IsReplayStart = true;

	STATEMANAGER->b_Relplay = false;
	STATEMANAGER->ReplayInit = true;
	STATEMANAGER->b_IsGameLevel = true;

	for (auto p : PARTICLEMANAGER->m_EmitterList)
	{
		if (p->type == ET_EXPLOSION)
		{
			p->isOn = false;
		}
	}
}