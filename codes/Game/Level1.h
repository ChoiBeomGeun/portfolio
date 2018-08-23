/******************************************************************************/
/*!
\file	level1.h
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

All levels is running in this state
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once
#include "BaseStage.h"
#include "CameraMovement.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Level1 :public BaseStage
{
public:
	Level1();
	~Level1();
	void Load(void);
	void Init(void);
	void Update(float dt);
	void Free(void);
	void Unload(void);

	static void loadbackground();
	
	bool moving;
	glm::vec3 playerInitPos;
private:
	glm::vec3 _playerPosition;
	float _camPaceSpeed;

	glm::vec3 _camPacedirction;
	glm::vec3 _camStartPosition;
	TE::CameraAction camAct;

private:
	int Level1Counter;
};