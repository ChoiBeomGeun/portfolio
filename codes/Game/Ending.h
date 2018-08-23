#pragma once
/******************************************************************************/
/*!
\file	Ending.h
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2018/5/29

Ending
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/


#pragma once
#include "BaseStage.h"
#include "CameraMovement.h"

class Ending :public BaseStage
{
public:

	Ending();
	~Ending();
	void Load(void);
	void Init(void);
	void Update(float dt);
	void Free(void);
	void Unload(void);

private:

};