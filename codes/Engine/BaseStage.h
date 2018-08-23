/******************************************************************************/
/*!
\file   BaseStage.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    Thumbup Engine
\date   2017/11/29

BaseStage for the level

*/
/******************************************************************************/
#pragma once
#include <vector>
class BaseStage
{
public:
	BaseStage(void);

virtual ~BaseStage(void);
	virtual void Load(void) = 0;
	virtual void Init(void) = 0;
	virtual	void Update(float dt) = 0;
	virtual  void Free(void) = 0;
	virtual	 void Unload(void) = 0;
	int NumberOfStage = 0;
	int WorldSizeX = 0;
	int WorldSizeY = 0;
};
