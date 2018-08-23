/******************************************************************************/
/*!
\file	Pause.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/04/19

Pause state source file
There are go to level select state,Pause state,How to play state,Quit the game
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#pragma once
#include "Pause.h"
#include "SoundManager.h"
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
#include "InGameLogic.h"
#include "Archetype.h"
#include "CameraMovement.h"
#include "Trigger.h"
#include "ObjectStyle.h"
using namespace TE;


Object * frame =nullptr;
Object * textIndicator = nullptr;
Object * iconRestart= nullptr;
Object * iconHowToPlay= nullptr;
Object * iconExit=nullptr;
Object * iconLevelSelect=nullptr;
Object * oHowToPlay = nullptr;
bool  HowTOplay = false;
Pause::Pause()
{

}

Pause::~Pause()
{
}

void Pause::Load()
{
	rotation_radius = 200;
	frame = FACTORY->CreateHUD(glm::vec3(0,0,0), glm::vec3(0,0,0));
	frame->GetComponent<Transform>()->scale = glm::vec3(300, 300, 0);
	textIndicator = FACTORY->CreateHUD(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	textIndicator->GetComponent<Transform>()->scale = glm::vec3(150, 150,0);

	iconRestart = FACTORY->CreateHUD(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	iconRestart->GetComponent<Transform>()->position = glm::vec3(rotation_radius,  0, 0);
	iconRestart->GetComponent<Transform>()->scale = glm::vec3(40, 40, 0);

	iconHowToPlay = FACTORY->CreateHUD(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	iconHowToPlay->GetComponent<Transform>()->position = glm::vec3(0, rotation_radius, 0);
	iconHowToPlay->GetComponent<Transform>()->scale = glm::vec3(40, 40, 0);


	iconExit = FACTORY->CreateHUD(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	iconExit->GetComponent<Transform>()->position = glm::vec3(0, -rotation_radius, 0);
	iconExit->GetComponent<Transform>()->scale = glm::vec3(40, 40, 0);


	iconLevelSelect = FACTORY->CreateHUD(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	iconLevelSelect->GetComponent<Transform>()->position = glm::vec3(-rotation_radius, 0, 0);
	iconLevelSelect->GetComponent<Transform>()->scale = glm::vec3(40, 40, 0);


	frame->GetComponent<Sprite>()->isRotating = true;
	textIndicator->GetComponent<Sprite>()->isRotating = true;
	iconRestart->GetComponent<Sprite>()->isRotating = true;
	iconHowToPlay->GetComponent<Sprite>()->isRotating = true;
	iconExit->GetComponent<Sprite>()->isRotating = true;
	iconLevelSelect->GetComponent<Sprite>()->isRotating = true;


	frame->GetComponent<Sprite>()->depth = 1;
	textIndicator->GetComponent<Sprite>()->depth = 2;
	PauseSound = SOUNDMANAGER->LoadSound("Menu.mp3");
	MoveSound = SOUNDMANAGER->LoadSound("Menumove.mp3");
	SelectSound = SOUNDMANAGER->LoadSound("Menuselect.mp3");


	frame->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("LevelSelction.png");
	textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Menu_Quit.png");

	frame->GetComponent<Sprite>()->isRotating = true; 
	textIndicator->GetComponent<Sprite>()->isRotating = true;
	iconRestart->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("question.png");
	iconExit->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("quit.png");
	iconHowToPlay->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Pause_restarticon.png");
	iconLevelSelect->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Pause_levelselecticon.png");


}

void Pause::Init()
{
	CreditsIsON = false;
	
	Selection = PauseList::Pause_Restart;
	delta_angle = 90;
	LeftRotate = false;
	RightRotate = false;
	IsRotating = false;
	IsTextChanged = false;
	IsSelected = false;
	selection_angle = 0;
	select_index = 0;
	SOUNDMANAGER->PauseAllSound();
	
}

void Pause::Update(float dt)
{/*
	if (HowTOplay) {


		if (Input::IsTriggered(SDL_SCANCODE_SPACE)) {
			SOUNDMANAGER->PlaySounds(SelectSound, false);
			HowTOplay = false;
			FACTORY->Destroy(oHowToPlay);
		}
	}*/


	for(auto obj : FACTORY->ObjectIDMap)
	{

		if (obj.second == frame ||
			obj.second == textIndicator ||
			obj.second == iconHowToPlay ||
			obj.second == iconExit ||
			obj.second == iconLevelSelect ||
			obj.second == iconRestart ||
			obj.second == obj_confirmationPause ||
			obj.second == oHowToPlay
		)
			continue;
		obj.second->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 100);

	}


		if (ConfirmationIsOn) {
			if (Input::IsTriggered(SDL_SCANCODE_Y))
				ENGINE->Quit();
			if (Input::IsTriggered(SDL_SCANCODE_N) || Input::IsTriggered(SDL_SCANCODE_ESCAPE))
			{
				ConfirmationIsOn = false;
				FACTORY->Destroy(obj_confirmationPause);
				return;
			}
		}
		if (ConfirmationIsOn)
			return;



		IsSelected = false;
		if (frame->GetComponent<Transform>()->angle == 360.f || frame->GetComponent<Transform>()->angle == -360.f)
		{
			frame->GetComponent<Transform>()->angle = 0.f;
			delta_angle = 90;
			select_index = 0;
		}
		PauseCam.Update(dt);

		if (IsRotating) {
			DeltaAngle();

		

			iconHowToPlay->GetComponent<Transform>()->position.x = cos(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (1) * 90)) * rotation_radius;
			iconHowToPlay->GetComponent<Transform>()->position.y = sin(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (1) * 90)) * rotation_radius;
			iconLevelSelect->GetComponent<Transform>()->position.x = cos(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (2) * 90)) * rotation_radius;
			iconLevelSelect->GetComponent<Transform>()->position.y = sin(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (2) * 90)) * rotation_radius;
			iconExit->GetComponent<Transform>()->position.x = cos(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (3) * 90)) * rotation_radius;
			iconExit->GetComponent<Transform>()->position.y = sin(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (3) * 90)) * rotation_radius;
			iconRestart->GetComponent<Transform>()->position.x = cos(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (4) * 90)) * rotation_radius;
			iconRestart->GetComponent<Transform>()->position.y = sin(TUMath::DegreeToRadian(frame->GetComponent<Transform>()->angle + (4) * 90)) * rotation_radius;
		}
		else
		{
			delta_angle = frame->GetComponent<Transform>()->angle;
			IsTextChanged = false;
			Selection_Text();
		}

		if (!IsSelected && !IsRotating)
			if (Input::IsTriggered(SDL_SCANCODE_SPACE) || Input::IsTriggered(SDL_SCANCODE_RETURN))
			{
				SOUNDMANAGER->PlaySounds(SelectSound, false);
				IsSelected = true;
			}
		if (IsSelected)
		{
			switch (Selection)
			{
			case PauseList::Pause_Restart:
				STATEMANAGER->Restart();


				break;
			case PauseList::Pause_Exit:
				STATEMANAGER->b_IsReplay = false;
				STATEMANAGER->b_Relplay = false;
				STATEMANAGER->b_IsPauseFirst = true;
				CAMERA->cameraUp.x = 0;
				CAMERA->cameraUp.y = 1;
				TRIGGERLOGIC->InitDegree();
				STATEMANAGER->PauseReturn();
				STATEMANAGER->MoveState(3);
				return;
				break;
			case PauseList::Pause_HowToPlay:

				obj_confirmationPause = FACTORY->CreateHUD(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
				obj_confirmationPause->GetComponent<Transform>()->position = glm::vec3(0, 0, 0);
				obj_confirmationPause->GetComponent<Transform>()->scale = glm::vec3(650, 250, 0);
				obj_confirmationPause->GetComponent<Sprite>()->depth = 3;
				if(!APP->IsKRMODE)
				obj_confirmationPause->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Sure.png");
				else
					obj_confirmationPause->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("kr_Sure.png");
				ConfirmationIsOn = true;
				return;
				break;

			case PauseList::Pause_LevelSelect:
			{
				if (HowTOplay)
				{
					HowTOplay = false;
					FACTORY->Destroy(oHowToPlay);
					return;
				}
				oHowToPlay = FACTORY->CreateHUD(glm::vec3(0,0, 0), glm::vec3(0, 0, 0));
				oHowToPlay->GetComponent<Transform>()->position = glm::vec3(500, 0, 0);
				oHowToPlay->GetComponent<Transform>()->scale = glm::vec3(500, 150, 0);
				oHowToPlay->GetComponent<Sprite>()->depth =5;
				oHowToPlay->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("howTOPlay2.png");
				HowTOplay = true;
			}
			}
		}


		if (!LeftRotate && !IsRotating && !IsTextChanged)
			if (Input::IsPressed(SDL_SCANCODE_LEFT)) {
				LeftRotate = true;
				IsRotating = true;
				++select_index;
				Selection_plus();
				IsTextChanged = true;

				SOUNDMANAGER->PlaySounds(MoveSound, false);
			}
			else if (!RightRotate && !IsRotating && !IsTextChanged)
				if (Input::IsPressed(SDL_SCANCODE_RIGHT)) {
					RightRotate = true;
					IsRotating = true;
					--select_index;
					Selection_minus();
					IsTextChanged = true;

					SOUNDMANAGER->PlaySounds(MoveSound, false);
				}

		if (LeftRotate)
		{
			if (IsRotating) {

				frame->GetComponent<Transform>()->angle += 250 * dt;

			}
			else
				LeftRotate = false;
		}
		else if (RightRotate)
		{
			if (IsRotating)
				frame->GetComponent<Transform>()->angle -= 250 * dt;
			else
				RightRotate = false;
		}

	


}




void Pause::Free(void)
{

	SOUNDMANAGER->ResumeAllSound();
	if(frame)
	FACTORY->Destroy(frame);
	if (textIndicator)
	FACTORY->Destroy(textIndicator);
	if (iconRestart)
	FACTORY->Destroy(iconRestart);
	if (iconHowToPlay)
	FACTORY->Destroy(iconHowToPlay);
	if (iconExit)
	FACTORY->Destroy(iconExit);
	if (iconLevelSelect)
	FACTORY->Destroy(iconLevelSelect);
	if (oHowToPlay)
	FACTORY->Destroy(oHowToPlay);


	for (auto obj : FACTORY->ObjectIDMap)
	{
		if(obj.second->objectstyle != Objectstyle::BackGround)
		obj.second->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);

	}
}

void Pause::Unload()
{
}

void Pause::DeltaAngle(void)
{
	if (abs(frame->GetComponent<Transform>()->angle - delta_angle) >= 90)
	{
		IsRotating = false;
		delta_angle = frame->GetComponent<Transform>()->angle;
		if (delta_angle > 0)
			frame->GetComponent<Transform>()->angle = 90 * float(select_index);

		if (delta_angle < 0)
			frame->GetComponent<Transform>()->angle = -90 * float(abs(select_index));
	}
}

void Pause::Selection_plus(void)
{
	switch (Selection)
	{
	case PauseList::Pause_Restart:  Selection = PauseList::Pause_LevelSelect; 
		break;
	case PauseList::Pause_LevelSelect: Selection = PauseList::Pause_HowToPlay;
		break;
	case PauseList::Pause_HowToPlay: Selection = PauseList::Pause_Exit; 
		break;
	case PauseList::Pause_Exit: Selection = PauseList::Pause_Restart; 
		break;
	default:
		break;
	}
}

void Pause::Selection_minus(void)
{
	switch (Selection)
	{
	case PauseList::Pause_LevelSelect: Selection = PauseList::Pause_Restart;
		break;
	case PauseList::Pause_HowToPlay: Selection = PauseList::Pause_LevelSelect;
		break;
	case PauseList::Pause_Exit:Selection = PauseList::Pause_HowToPlay;
		break;
	case PauseList::Pause_Restart: Selection = PauseList::Pause_Exit;
		break;
	default:
		break;
	}
}

void Pause::Selection_Text(void)
{
	switch (Selection)
	{

	case PauseList::Pause_LevelSelect: 
		if (!APP->IsKRMODE)
		textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Menu_HowToPlay.png");
		else
			textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("kr_Menu_HowToPlay.png");

		break;
	case PauseList::Pause_HowToPlay: 
		if (!APP->IsKRMODE)
		textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Menu_Quit.png");
		else
			textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("kr_Menu_Quit.png");
		break; 
	case PauseList::Pause_Exit:
		if (!APP->IsKRMODE)
		textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Pause_levelseclect.png");
		else
			textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("kr_Pause_levelseclect.png");
		break; 
	case PauseList::Pause_Restart: 
		if (!APP->IsKRMODE)
		textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("Pause_Restart.png");
		else
			textIndicator->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id("kr_Pause_Restart.png");
		break;
	default:
		break;
	}
}

void Pause::resize()
{
	if (APP->_screenWidth != 1280 && APP->_screenHeight != 720)
	{
		frame->GetComponent<Transform>()->scale.x = APP->_screenWidth * frame->GetComponent<Transform>()->scale.x / 1280;
		frame->GetComponent<Transform>()->scale.y = frame->GetComponent<Transform>()->scale.x;

		textIndicator->GetComponent<Transform>()->scale.x = APP->_screenWidth * textIndicator->GetComponent<Transform>()->scale.x / 1280;
		textIndicator->GetComponent<Transform>()->scale.y = textIndicator->GetComponent<Transform>()->scale.x;


		iconRestart->GetComponent<Transform>()->scale.x = APP->_screenWidth * iconRestart->GetComponent<Transform>()->scale.x / 1280;
		iconRestart->GetComponent<Transform>()->scale.y = APP->_screenHeight * iconRestart->GetComponent<Transform>()->scale.y / 720;


		iconHowToPlay->GetComponent<Transform>()->scale.x = APP->_screenWidth * iconHowToPlay->GetComponent<Transform>()->scale.x / 1280;
		iconHowToPlay->GetComponent<Transform>()->scale.y = APP->_screenHeight * iconHowToPlay->GetComponent<Transform>()->scale.y / 720;

		iconExit->GetComponent<Transform>()->scale.x = APP->_screenWidth * iconExit->GetComponent<Transform>()->scale.x / 1280;
		iconExit->GetComponent<Transform>()->scale.y = APP->_screenHeight * iconExit->GetComponent<Transform>()->scale.y / 720;

		iconLevelSelect->GetComponent<Transform>()->scale.x = APP->_screenWidth * iconLevelSelect->GetComponent<Transform>()->scale.x / 1280;
		iconLevelSelect->GetComponent<Transform>()->scale.y = APP->_screenHeight * iconLevelSelect->GetComponent<Transform>()->scale.y / 720;
		
	}
}
