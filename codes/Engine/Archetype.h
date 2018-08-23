/******************************************************************************/
/*!
\file   ArchtypeEditor.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Imgui Archetype Editor
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once

#include"glm\vec3.hpp"
#include"ObjectStyle.h"

#include "Component.h"
#include "ComponentType.h"
#include "json\json.h"
#include "json\JsonClass.h"
#include <vector>
namespace TE {

	class Archetype {
	public:
		std::string ArchetypeName{"Default"};
		glm::vec3 DefaultPosition{ 0,0,0 };
		glm::vec3 DefaultScale{ 0,0,0 };
		std::string DefaultTexture;
		std::string  DefaultObjectStyle;
		std::vector<ComponentType>HavingComponents;
		float rotation{ 0 };
		float mass{ 0 };
		bool GravityOn = false;
		bool _180triggerornot = false;



	};

	Archetype ReadingArchetype(std::string path);

}





