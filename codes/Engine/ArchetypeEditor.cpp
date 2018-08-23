/******************************************************************************/
/*!
\file   ArchtypeEditor.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM200
\par    ThumbUp Engine
\date   2017/11/29

Imgui Archetype Editor
All content 2017 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "ArchetypeEditor.h"

using namespace TE;

Archetype TE::ReadingArchetype(std::string path)
{
	char * Userinfo;
	size_t len = path.size();
	_dupenv_s(&Userinfo, &len, "USERPROFILE");




	std::string saveLevel = path;
#ifdef _DEBUG
	path = ".\\Archtypes.\\" + path;
#else
	path = Userinfo;
	path += "/Documents/RoteRote/Archtypes/" + saveLevel;
#endif
	free(Userinfo);


	Jsonclass file;


	//	char *path = (char*)JSON_FILE;
	file.ReadFile(path);


	Archetype temp;
	temp.ArchetypeName = file.mRoot.get("ArchtypeName", false).asString();
	temp.DefaultObjectStyle = file.mRoot.get("ObjectStyle", false).asString();
	temp.DefaultPosition.x = file.mRoot.get("DefaultPosition", false).get("x", false).asFloat();
	temp.DefaultPosition.y = file.mRoot.get("DefaultPosition", false).get("y", false).asFloat();
	temp.DefaultPosition.z = file.mRoot.get("DefaultPosition", false).get("z", false).asFloat();

	temp.DefaultScale.x = file.mRoot.get("DefaultScale", false).get("x", false).asFloat();
	temp.DefaultScale.y = file.mRoot.get("DefaultScale", false).get("y", false).asFloat();
	temp.DefaultScale.z = file.mRoot.get("DefaultScale", false).get("z", false).asFloat();

	temp.DefaultTexture = file.mRoot.get("DefaultTexture", false).asString();

	temp.GravityOn = file.mRoot.get("DefaultGravity",false).asBool();

	temp.rotation= file.mRoot.get("DefaultRotation", false).asFloat();
		temp.mass= file.mRoot.get("DefaultMass", false).asFloat();
		temp._180triggerornot = file.mRoot.get("DefaultTrigger180ornot", false).asBool();

	for (int i = 0; i < file.mRoot.get("HavingComponentsNumbers", false).asInt(); i++)
	{
		if (file.mRoot["HavingComponents"][i].asString() == "BODY")
			temp.HavingComponents.push_back(CT_BODY);
		if (file.mRoot["HavingComponents"][i].asString() == "TRANSFORM")
			temp.HavingComponents.push_back(CT_TRANSFORM);
		if (file.mRoot["HavingComponents"][i].asString() == "CONTROLLER")
			temp.HavingComponents.push_back(CT_CONTROLLER);
		if (file.mRoot["HavingComponents"][i].asString() == "SPRITE")
			temp.HavingComponents.push_back(CT_SPRITE);
		if (file.mRoot["HavingComponents"][i].asString() == "TRIGGER")
			temp.HavingComponents.push_back(CT_TRIGGER);
		if (file.mRoot["HavingComponents"][i].asString() == "BUTTON")
			temp.HavingComponents.push_back(CT_BUTTON);
		if (file.mRoot["HavingComponents"][i].asString() == "PARTICLE")
			temp.HavingComponents.push_back(CT_EMITTER);
	}

	return temp;
}

void TE::SavingArchtype(Archetype pArche)
{
	std::string path = pArche.ArchetypeName + ".json";
	char * Userinfo;
	size_t len = 15;
	_dupenv_s(&Userinfo, &len, "USERPROFILE");




	std::string saveLevel = path;
#ifdef _DEBUG
	path = ".\\Archtypes.\\" + path;
#else
	path = Userinfo;
	path += "/Documents/RoteRote/Archtypes/" + saveLevel;
#endif
	free(Userinfo);

	Jsonclass file;
	Json::Value root;


	root["ArchtypeName"] = pArche.ArchetypeName;
	root["DefaultPosition"]["x"] = pArche.DefaultPosition.x;
	root["DefaultPosition"]["y"] = pArche.DefaultPosition.y;
	root["DefaultPosition"]["z"] = pArche.DefaultPosition.z;
	root["DefaultScale"]["x"] = pArche.DefaultScale.x;
	root["DefaultScale"]["y"] = pArche.DefaultScale.y;
	root["DefaultScale"]["z"] = pArche.DefaultScale.z;
	root["DefaultRotation"] = pArche.rotation;
	root["DefaultMass"] = pArche.mass;
	root["DefaultGravity"] = pArche.GravityOn;
	root["DefaultTrigger180ornot"] = pArche._180triggerornot;


	root["ObjectStyle"] = pArche.DefaultObjectStyle;
	root["DefaultTexture"] = pArche.DefaultTexture;
	int i = 0;
	for (auto it : pArche.HavingComponents) {

		switch (it) {
		case CT_BODY:
			root["HavingComponents"][i] = "BODY";
			break;
		case CT_TRANSFORM:
			root["HavingComponents"][i] = "TRANSFORM";
			break;
		case CT_SPRITE:
			root["HavingComponents"][i] = "SPRITE";
			break;
		case CT_CONTROLLER:
			root["HavingComponents"][i] = "CONTROLLER";
			break;
		case CT_BUTTON:
			root["HavingComponents"][i] = "BUTTON";
			break;
		case CT_TRIGGER:
			root["HavingComponents"][i] = "TRIGGER";
			break;
		case CT_EMITTER:
			root["HavingComponents"][i] = "PARTICLE";
			break;

	
		}
		i++;
		
	}
	root["HavingComponentsNumbers"] = i;


	file.WriteFile(path, root);
}