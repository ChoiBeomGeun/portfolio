/******************************************************************************/
/*!
\file   LevelManager.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Using jsoncpp, loading and saving the level
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "LevelManager.h"
#include "json/json.h"
#include "json/JsonClass.h"
#include "Factory.h"
#include "Object.h"
#include "DebugUtil.h"
#include  "StateManager.h"
#include  "stdlib.h"
#include "camera.h"
#include "Particles.h"
#include "..\..\example\examples\PlayerController.h"
#include "..\..\example\examples\InGameLogic.h"
#include "ParticleManager.h"
#define JSON_FILE "jsonFile.json"
#define JSON_FILE_WRITE "jsonFileWrite.json"
using namespace TE;
using namespace  std;

namespace TE {


	LevelManager * LEVELMANAGER = nullptr;


}
struct StringCompareLevel {

	bool operator()(const std::string& a, const std::string& b)
		const {
			return std::atoi(&a.at(5)) > std::atoi(&b.at(5));
	
	}

};
float scaleFactor = 1.f;
LevelManager::LevelManager()
{

;

}



void LevelManager::LoadLevel(std::string  path)
{
 	string PaticlePath;
	
	std::string saveLevel = path;

	path = ".\\levels.\\" + path;

	STATEMANAGER->Loadtolevelname = saveLevel;
	Jsonclass file;
	std::string object = "Object";
	
	file.ReadFile(path);



	for (int i = 1; i< file.mRoot.get("NumberOfObjects", false).asInt() + 1; i++)
	{
		std::string Objectstyle = file.mRoot.get(object + to_string(i), false).get("ObjectType", false).asString();


		Object *tempObject = FACTORY->CreateEmptyObject(); 		

		bool GravityOn = file.mRoot.get(object + to_string(i), false).get("GravityOn", false).asBool();
		float Xpos = file.mRoot.get(object + to_string(i), false).get("Position", false).get("x", false).asFloat();
		float Ypos = file.mRoot.get(object + to_string(i), false).get("Position", false).get("y", false).asFloat();
		float Rotation = file.mRoot.get(object + to_string(i), false).get("Rotation", false).asFloat();
		float Xscale = file.mRoot.get(object + to_string(i), false).get("Scale", false).get("x", false).asFloat();
		float Yscale = file.mRoot.get(object + to_string(i), false).get("Scale", false).get("y", false).asFloat();
		std::string textureDir = file.mRoot.get(object + to_string(i), false).get("TextureDir", false).asString();
		CAMERA->cameraPos.x = file.mRoot.get("DefalutCamera", false).get("EYE", false).get("x", false).asFloat();
		CAMERA->cameraPos.y = file.mRoot.get("DefalutCamera", false).get("EYE", false).get("y", false).asFloat();
		CAMERA->cameraPos.z = file.mRoot.get("DefalutCamera", false).get("EYE", false).get("z", false).asFloat();
		float mass = file.mRoot.get(object + to_string(i), false).get("Mass", false).asFloat();

		
		for (unsigned int indexC = 0; ;indexC++) {
			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "TRANSFORM") {
				tempObject->AddComponent<Transform>();
				tempObject->GetComponent<Transform>()->position.x = Xpos;
				tempObject->GetComponent<Transform>()->position.y = Ypos;
				tempObject->GetComponent<Transform>()->scale.x = Xscale;
				tempObject->GetComponent<Transform>()->scale.y = Yscale;
				tempObject->GetComponent<Transform>()->scale *= scaleFactor;
				tempObject->GetComponent<Transform>()->angle = Rotation;
				tempObject->GetComponent<Transform>()->rotation = glm::vec3(0, 0, 1);
			}
			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "SPRITE") {
				tempObject->AddComponent<Sprite>();
 				tempObject->GetComponent<Sprite>()->depth = file.mRoot[object + to_string(i)]["Depth"].asFloat();
				tempObject->GetComponent<Sprite>()->ChangeColor(255, 255, 255, 255);
				tempObject->GetComponent<Sprite>()->isPerspective = true;
				tempObject->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id(textureDir);				
			}
			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "CONTROLLER") {
				tempObject->AddComponent<PlayerController>();
			}
			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "BODY") {
 				tempObject->AddComponent<Body>();
				tempObject->GetComponent<Body>()->gravityOn = GravityOn;
				tempObject->GetComponent<Body>()->pm_invmass = mass;
				tempObject->GetComponent<Body>()->restitution = 0;
			}
	
			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "BUTTON") {
				tempObject->objectstyle = Objectstyle::Button;
			

			}
			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "ANIMATION") {
				tempObject->AddComponent<Animation>();
				tempObject->GetComponent<Animation>()->setFlipX(false);
				tempObject->GetComponent<Animation>()->setTime(0.f);
				tempObject->GetComponent<Animation>()->isJumping = false;
				tempObject->GetComponent<Animation>()->setPressed(false);

			}
			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "TRIGGER") {
				tempObject->AddComponent<Trigger>();
				if (Objectstyle == "Trigger180") {
					tempObject->GetComponent<Trigger>()->TriggerType = "180";
					tempObject->objectstyle = Objectstyle::Trigger180;

				}

				if (Objectstyle == "Trigger90") {
					tempObject->GetComponent<Trigger>()->TriggerType = "90";
					tempObject->objectstyle = Objectstyle::Trigger90;
				}


				if (Objectstyle == "Trigger90Right") {
					tempObject->GetComponent<Trigger>()->TriggerType = "90";
					tempObject->objectstyle = Objectstyle::Trigger90;
				}

				tempObject->GetComponent<Trigger>()->MaxLife = file.mRoot.get(object + to_string(i), false).get("TriggerLifeTime", false).asInt();
			}

			if (file.mRoot[object + to_string(i)]["Components"][indexC].asString() == "")
				break;
		}
		
		if (Objectstyle == "Player")
		{
			tempObject->objectstyle = Objectstyle::Player;
			tempObject->GetComponent<Sprite>()->depth = 10.f;
		}
		else if (Objectstyle == "Asteriod")
		{
			tempObject->objectstyle = Objectstyle::Asteriod;
		}
		else if (Objectstyle == "Wall")
		{
			tempObject->objectstyle = Objectstyle::Wall;
		}
		else if (Objectstyle == "AttachWall")
		{
			tempObject->objectstyle = Objectstyle::AttachWall;
		}
		else if (Objectstyle == "Button")
		{
			tempObject->objectstyle = Objectstyle::Button;
		}
		else if (Objectstyle == "Box")
		{
			tempObject->objectstyle = Objectstyle::Box;
			int x, y;

			if (static_cast<int>(tempObject->GetComponent<Transform>()->scale.x) % 20 == 0)
				x = 1;
			else
				x = static_cast<int>(tempObject->GetComponent<Transform>()->scale.x) / 40;
			if (static_cast<int>(tempObject->GetComponent<Transform>()->scale.y) % 20 == 0)
				y = 1;
			else
				y = static_cast<int>(tempObject->GetComponent<Transform>()->scale.x) / 40;

			tempObject->GetComponent<Transform>()->u_v.x = static_cast<float>(x);
			tempObject->GetComponent<Transform>()->u_v.y = static_cast<float>(y);
		}
		else if (Objectstyle == "Trigger90")
		{
			tempObject->objectstyle = Objectstyle::Trigger90;
			
		}
		else if (Objectstyle == "Trigger90Right")
		{
			tempObject->objectstyle = Objectstyle::Trigger90Right;
		}
		else if (Objectstyle == "Trigger180")
		{
			tempObject->objectstyle = Objectstyle::Trigger180;
		}
		else if (Objectstyle == "Clearzone")
		{
			tempObject->objectstyle = Objectstyle::Clearzone;
		}

		else if (Objectstyle == "Hazard")
		{
			tempObject->objectstyle = Objectstyle::Hazard;
		}
		else if (Objectstyle == "AttachWall")
		{
			tempObject->objectstyle = Objectstyle::AttachWall;
		}
		else if (Objectstyle == "AttachBox")
		{
			tempObject->objectstyle = Objectstyle::AttachBox;
		}
		else
			DEBUG_ASSERT(true, "Invaild Object Style");

		if (tempObject->GetComponent<Sprite>())
		{
			FACTORY->ObjectIDMap[tempObject->objID]->GetComponent<Sprite>()->mTexutureDir = (const_cast<char*>(textureDir.c_str()));
			tempObject->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id(const_cast<char*>(textureDir.c_str()));
		}
	
		tempObject->Initialize();
 	}

  }

void LevelManager::SaveLevel(std::string  path)
{
	FACTORY->ObjectIDMap;
	char * Userinfo;
	size_t len = path.size();
	_dupenv_s(&Userinfo, &len, "USERPROFILE");
	
	std::string saveLevel = path;

	path = ".\\levels.\\" + path;


	free(Userinfo);
	Jsonclass file;
	Json::Value root;
	std::string object = "Object";
        int NumberofUnvaildObject = 0;
        for (auto it : FACTORY->ObjectIDMap)
        {

			if (it.second->objectstyle == Objectstyle::BackGround|| it.second->objectstyle == Objectstyle::Particle ||it.second->objectstyle == Objectstyle::Button && it.second->GetComponent<Sprite>()->isPerspective
				== false && !it.second->HasComponent<Emitter>()) {
                NumberofUnvaildObject++;
                continue;
            }
        }

	root["Level"] =  1;
	root["WorldSize"]["x"] = STATEMANAGER->v_StatesLists[STATEMANAGER->i_CurrentStateNumber]->WorldSizeX;
	root["WorldSize"]["y"] = STATEMANAGER->v_StatesLists[STATEMANAGER->i_CurrentStateNumber]->WorldSizeY;
	root["DefalutCamera"]["EYE"]["x"] = CAMERA->cameraPos.x;
	root["DefalutCamera"]["EYE"]["y"] = CAMERA->cameraPos.y;
	root["DefalutCamera"]["EYE"]["z"] = CAMERA->cameraPos.z;
	root["DefalutCamera"]["TARGET"]["x"] = CAMERA->cameraTarget.x;
	root["DefalutCamera"]["TARGET"]["y"] = CAMERA->cameraTarget.y;
	root["DefalutCamera"]["TARGET"]["z"] = CAMERA->cameraTarget.z;
	root["DefalutCamera"]["UP"]["x"] = CAMERA->cameraUp.x;
	root["DefalutCamera"]["UP"]["y"] = CAMERA->cameraUp.y;
	root["DefalutCamera"]["UP"]["z"] = CAMERA->cameraUp.z;
	root["NumberOfObjects"] = FACTORY->ObjectIDMap.size()- NumberofUnvaildObject;
	int  i = 1;

    

	for (auto it : FACTORY->ObjectIDMap)
	{
		

		it.second->GetComponent<Transform>()->position.z = 0;
		static unsigned index = 0;


                if (it.second->objectstyle == Objectstyle::BackGround || it.second->objectstyle == Objectstyle::Particle ||it.second->objectstyle == Objectstyle::Button && it.second->GetComponent<Sprite>()->isPerspective
					== false &&!it.second->HasComponent<Emitter>()) {

                    continue;
                }

		if (it.second->GetComponent<Transform>() != nullptr) {
			root[object + to_string(i)]["Components"][index] = "TRANSFORM";
			index++;
		}
		if (it.second->GetComponent<Sprite>() != nullptr) {
			root[object + to_string(i)]["Components"][index] = "SPRITE";
			index++;
		}
		if (it.second->GetComponent<Body>() != nullptr) {
			root[object + to_string(i)]["Components"][index] = "BODY";

			if(it.second->objectstyle == Objectstyle::Box)
				it.second->GetComponent<Body>()->gravityOn = false;
			root[object + to_string(i)]["GravityOn"] = it.second->GetComponent<Body>()->gravityOn;
			index++;
		}
		if (it.second->GetComponent<Trigger>() != nullptr) {
			root[object + to_string(i)]["Components"][index] = "TRIGGER";
			root[object + to_string(i)]["TriggerType"] = it.second->GetComponent<Trigger>()->TriggerType;
			root[object + to_string(i)]["TriggerLifeTime"] = it.second->GetComponent<Trigger>()->LifeTime;
			index++;
		}
		if (it.second->GetComponent<Button>() != nullptr) {
			root[object + to_string(i)]["Components"][index] = "BUTTON";
			index++;
		}
		if (it.second->GetComponent<PlayerController>() != nullptr) {
			root[object + to_string(i)]["Components"][index] = "CONTROLLER";
			index++;
		}
		if (it.second->GetComponent<Animation>() != nullptr) {
			root[object + to_string(i)]["Components"][index] = "ANIMATION";
			index++;
		}

		index = 0;

		switch (it.second->objectstyle)
		{
		case Objectstyle::Player:
			root[object + to_string(i)]["ObjectType"] = "Player";
			break;
		case Objectstyle::Asteriod:
			root[object + to_string(i)]["ObjectType"] = "Asteriod";
			break;
		case Objectstyle::Wall:
			root[object + to_string(i)]["ObjectType"] = "Wall";
			break;
		case Objectstyle::Button:
			root[object + to_string(i)]["ObjectType"] = "Button";
			break;
		case Objectstyle::Box:
			root[object + to_string(i)]["ObjectType"] = "Box";
			break;
		case Objectstyle::AttachBox:
			root[object + to_string(i)]["ObjectType"] = "AttachBox";
			break;
		case Objectstyle::Trigger90:
			root[object + to_string(i)]["ObjectType"] = "Trigger90";
			break;
		case Objectstyle::Trigger180:
			root[object + to_string(i)]["ObjectType"] = "Trigger180";
			break;
		case Objectstyle::Clearzone:
			root[object + to_string(i)]["ObjectType"] = "Clearzone";
			break;

		case Objectstyle::AttachWall:
			root[object + to_string(i)]["ObjectType"] = "AttachWall";
			break;
		case Objectstyle::Trigger90Right:
			root[object + to_string(i)]["ObjectType"] = "Trigger90Right";
			break;
		case Objectstyle::Hazard:
			root[object + to_string(i)]["ObjectType"] = "Hazard";
			break;
		default:
			DEBUG_ASSERT(true, "Invaild Object Style");


		}
		root[object + to_string(i)]["ObjectID"] = i;
		root[object + to_string(i)]["Position"]["x"] = it.second->GetComponent<Transform>()->position.x;
		root[object + to_string(i)]["Position"]["y"] = it.second->GetComponent<Transform>()->position.y;
		root[object + to_string(i)]["Position"]["z"] = it.second->GetComponent<Transform>()->position.z;
		root[object + to_string(i)]["Scale"]["x"] = it.second->GetComponent<Transform>()->scale.x;
		root[object + to_string(i)]["Scale"]["y"] = it.second->GetComponent<Transform>()->scale.y;
		root[object + to_string(i)]["Depth"] = it.second->GetComponent<Sprite>()->depth;

		if (FACTORY->ObjectIDMap[it.first]->GetComponent<Body>() != nullptr)
			root[object + to_string(i)]["Mass"] = it.second->GetComponent<Body>()->pm_mass;
		root[object + to_string(i)]["Rotation"] = it.second->GetComponent<Transform>()->angle;


		root[object + to_string(i)]["TextureDir"] = FACTORY->ObjectIDMap[it.first]->GetComponent<Sprite>()->mTexutureDir;
		i++;
	}


	file.WriteFile(path, root);


}

void TE::LevelManager::SavingLevelInfo(void)
{
	std::string  path = "ClearInfo.json";
	char * Userinfo;
	size_t len = path.size();
	_dupenv_s(&Userinfo, &len, "USERPROFILE");


#ifdef _DEBUG
#else
	path = Userinfo;
	path += "/Documents/RoteRote/ClearInfo.json";
#endif
	free(Userinfo);

	
	Jsonclass file;
	Json::Value root;


	for (auto levelname : STATEMANAGER->vsLevelListandclear)
	{
		root[levelname.first] = levelname.second;



	}
	root["NumberOfTheLevels"] = STATEMANAGER->vsLevelListandclear.size();
	
	file.WriteFile(path, root);
}

void TE::LevelManager::LoadingLevelInfo(void)
{

 	std::string  path = "ClearInfo.json";
	char * Userinfo;
	size_t len = path.size();
	_dupenv_s(&Userinfo, &len, "USERPROFILE");
#ifdef _DEBUG
#else
	path = Userinfo;
	path += "/Documents/RoteRote/ClearInfo.json";
#endif
	free(Userinfo);

	Jsonclass file;
	std::string object = "Object";


	file.ReadFile(path);
	for (auto levelname : INGAMELOGIC->vsLevelList)
	{
		STATEMANAGER->vsLevelListandclear.push_back(std::pair<std::string, bool>(levelname, file.mRoot.get(levelname, false).asBool()));

	}
}



