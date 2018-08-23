/******************************************************************************/
/*!
\file   StateManager.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

State Manager header file in the engine system class
*/
/******************************************************************************/
#pragma once





#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Factory.h"
#include <vector>
#include "System.h"
#include  "BaseStage.h"
#include  "GameStateList.h"
#include <glm/glm.hpp>
#include <forward_list>
#include <queue>

namespace TE {

	class StateManager :public Systems {
	public:
		StateManager();
		~StateManager();

		void AddState(BaseStage* states);
		void SetStartState(int StateNumber);
		void SetPauseState(int StateNumber) { i_PauseStageNumber = StateNumber; }
		void SetReplayState(int StateNumber) { i_ReplayStageNumber = StateNumber; }

		void Initialize(void) override;
		void Update(float dt) override;
		void MoveState(int StateNumber);
		void Quit(void);
		void Restart(void);
		void Next(void);
		void Pause(void);
		void RestartReplay(void);
		void PauseReturn(void);
		void Replay(void);
		void ReplayReturn(void);
		void DestoryAllStates(void);
		bool b_Replayrestart = false;;
		bool b_IsDelay = true;
		bool b_IsPauseOn;
		bool b_IsRotating = false;
		bool b_IsGravityChanged;
		bool b_IsReplayStart = false;
		bool b_IsReplay = false;
		bool b_IsPauseFirst = true;
		bool b_IsRot90 = false;
		bool b_IsRot180 = false;
		bool b_Relplay = false;
		bool IsDrawing;
		bool levelreplay = false;
		bool ReplayInit = true;
		bool IsEnding = false;
		bool IsEndingISOVER = false;
		std::vector<std::pair<std::string, bool>> vsLevelListandclear;
		glm::vec3 InitplayerPos{ 0,0,0 };
		std::queue<ReplayerInfo> Replayerinfo;
		std::vector <std::pair<float, float>> AniSave;
		std::vector<BaseStage*> v_StatesLists;
		std::string Loadtolevelname;
		int i_CurrentStateNumber;
		int i_LevelSelect = 1;
		int i_NumberOfstage;
		int i_StageToMove;
		int i_PauseStageNumber;
		int i_ReplayStageNumber;
		bool LogicShutdown = false;
		bool b_IsRestart;
		bool b_IsNext;
		bool b_IsPrev;
		bool b_IsQuit;
		bool b_IsFirst;
		bool b_IsMoveState;
		bool b_IsReplayFirst = true;
		bool forceLevelLoading{ false };
		bool b_IsGameLevel{ false };
		bool b_IsAutoplaying{ false };
	};


	extern StateManager* STATEMANAGER;
}
#endif