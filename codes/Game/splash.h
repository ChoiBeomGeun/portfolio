/******************************************************************************/
/*!
\file	splash.h
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Splash State header interface
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/


#pragma once
#include "BaseStage.h"
#include "CameraMovement.h"

class splash :public BaseStage
{
public:

	splash();
	~splash();
	void Load(void);
	void Init(void);
	void Update(float dt);
	void Free(void);
	void Unload(void);

private:
	int MenuCounter;
	TE::CameraAction camActSplash;

};