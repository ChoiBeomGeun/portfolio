/******************************************************************************/
/*!
\file	logging.cpp
\author	Choi Beom Geun
\par	email: o77151@gmail.com
\par	Class:GAM250
\par	ThumbUp Engine
\date	2017/11/29

Logging system for playtesting source file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "logging.h"
#include "Trigger.h"
#include "StateManager.h"
#include "Engine.h"
#include <algorithm>
#include <ctime>
#include <chrono>
#include <iomanip>
#define LOG_NAME "Beta"
#define LOGGINGSTART true

struct LogList
{
	std::string Levelname = "default";
	int HowManyLose= 0;
	float HowMuchTimepassed= 0;
	float HowMuchTimeToWin = 0;
	int NumberOfTriggerActivation = 0;

};
struct int_compare {

	bool operator()(const LogList& a, const LogList& b)

		const {

		return std::atoi(&a.Levelname.at(5)) > std::atoi(&b.Levelname.at(5));
	}

};


typedef std::vector<LogList> LogItemLists;
LogItemLists GameLevelList;
std::vector<int> Howmanylose;
bool LoggingInit = true;
bool DataInit = true;
bool IsLoseOnce = true;
using namespace TE;
namespace TE {


	LoggingSystem * LOGGINGSYSTEM ;


}
TE::LoggingSystem::LoggingSystem()
{
	IsLoggigOn = ENGINE->IsLoggingOn;
	if (ENGINE->IsLoggingOn) {


		if (LoggingInit) {
			for (auto it : ENGINE->mVsLevelnamelist)
			{
				if (*it.begin() == 'l')
				{
					LogList temp;
					temp.HowManyLose = 0;
					temp.HowMuchTimepassed = 0;
					temp.Levelname = it;
					GameLevelList.push_back(temp);
				}
			}
			LoggingInit = false;
		
		}
	
	std::sort(GameLevelList.begin(), GameLevelList.end(), int_compare());
	std::reverse(GameLevelList.begin(), GameLevelList.end());
	GameLevelList.erase(GameLevelList.begin());
	}
}


void TE::LoggingSystem::Initialize()
{
	for (auto levels : GameLevelList)
	{

		levels.HowManyLose = 0;
	}
	IsLoseOnce = true;
}

void TE::LoggingSystem::Update(float dt)
{	

	if (ENGINE->IsLoggingOn) {
 		GameLevelList[STATEMANAGER->i_LevelSelect - 1].NumberOfTriggerActivation = TRIGGERLOGIC->NumberOfTriggersActivation;
		if (APP->b_Lose&& IsLoseOnce)
		{
			GameLevelList[STATEMANAGER->i_LevelSelect - 1].HowManyLose++;
			IsLoseOnce = false;

		}
		GameLevelList[STATEMANAGER->i_LevelSelect - 1].HowMuchTimepassed += dt;
		GameLevelList[STATEMANAGER->i_LevelSelect - 1].HowMuchTimeToWin += dt;


		if (APP->b_Lose)
		{

			GameLevelList[STATEMANAGER->i_LevelSelect - 1].HowMuchTimeToWin = 0;


		}

	}
}

void TE::LoggingSystem::SavingLog(void)
{
	if (ENGINE->IsLoggingOn) {
		LOGGINGSYSTEM->rootlog["LOG NAME"] = LOG_NAME;

		char buff[20];
		time_t now = time(NULL);
		strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
		std::string date = buff;
		LOGGINGSYSTEM->rootlog["Date"] = date;
		int LogSize = (int)ENGINE->mVsLognamelist.size() + 1;
		std::string pathto = "playerlog";
		pathto = pathto + std::to_string(LogSize) + ".json";	
		std::string saveLevel = pathto;
		pathto = ".\\logging.\\" + pathto;
		LOGGINGSYSTEM->rootlog["HowMuchTimePassedInGame"] = ENGINE->HowMuchTimePassedInGame;
		for (auto it : GameLevelList)
		{

			LOGGINGSYSTEM->rootlog[it.Levelname]["HowManyLose"] = it.HowManyLose;
			LOGGINGSYSTEM->rootlog[it.Levelname]["HowMuchTimePassedInLevel"] = it.HowMuchTimepassed;
			LOGGINGSYSTEM->rootlog[it.Levelname]["HowMuchTimePassedToWin"] = it.HowMuchTimeToWin;
			LOGGINGSYSTEM->rootlog[it.Levelname]["NumberOfTriggerActivation"] = it.NumberOfTriggerActivation;
		}
		files.WriteFile(pathto, LOGGINGSYSTEM->rootlog);
	}

}

void TE::LoggingSystem::Free(void)
{

}

TE::LoggingSystem::~LoggingSystem()
{	



}
