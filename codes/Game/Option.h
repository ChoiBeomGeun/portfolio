/******************************************************************************/
/*!
\file	Option.h
\author	Kyungook.Park
\par	email: qkrruddn6680@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/12/19

Option state header file
There are go to level select state,option state,How to play state
,Quit the game
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#pragma once
#include "BaseStage.h"
#include "StateLists.h"
#include "OptionList.h"
#include "CameraMovement.h"

class Option :public BaseStage
{
public:
	Option();
	~Option();
	void Load(void);
	void Init(void);
	void Update(float dt);
	void Free(void);
	void Unload(void);

	void DeltaAngle(void);

	void Selection_plus(void);
	void Selection_minus(void);

	void Selection_Text(void);

private:
	TE::CameraAction OptionCam;
	bool LeftRotate;
	bool RightRotate;
	bool ConfirmationIsOn = false;
	bool CreditsIsON = false;
	bool IsRotating;
	bool IsSelected;
	bool IsTextChanged;
	bool IsSoundOn = true;
	int select_index;
	unsigned int Option_SoundOnOff;	
	unsigned int Option_Credits;
	unsigned int Option_Back;
	unsigned int Option_Full;

	OptionList Selection;

	float delta_angle;
	int selection_angle;

	int rotation_radius;

	unsigned int OptionSound;
	unsigned int MoveSound;
	unsigned int SelectSound;
};
