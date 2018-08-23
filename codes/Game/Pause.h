/******************************************************************************/
/*!
\file	Pause.h
\author	Choi Beom Geun
\par	email: 	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/12/19

Pause state header file
There are go to level select state, Pause state, How to play state
Quit the game
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#pragma once
#include "BaseStage.h"
#include "StateLists.h"
#include "PauseList.h"
#include "CameraMovement.h"

class Pause :public BaseStage
{
public:
	Pause();
	~Pause();
	void Load(void);
	void Init(void);
	void Update(float dt);
	void Free(void);
	void Unload(void);

	void DeltaAngle(void);

	void Selection_plus(void);
	void Selection_minus(void);

	void Selection_Text(void);
	void resize();
private:
	TE::CameraAction PauseCam;
	bool LeftRotate;
	bool RightRotate;
	bool ConfirmationIsOn = false;
	bool CreditsIsON = false;
	bool IsRotating;
	bool IsSelected;
	bool IsTextChanged;
	bool IsSoundOn = true;
	int select_index;
	unsigned int Pause_Restart;		//Is it Okay To sign texture as just int not unsigned int
	unsigned int Pause_Exit;
	unsigned int Pause_HowToPlay;
	unsigned int Pause_LevelSelect;

	TE::Object* obj_howToPlayPause;
	TE::Object* obj_confirmationPause;
	PauseList Selection;

	float delta_angle;
	int selection_angle;

	float rotation_radius;

	unsigned int PauseSound;
	unsigned int MoveSound;
	unsigned int SelectSound;
};
