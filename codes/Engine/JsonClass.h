/******************************************************************************/
/*!
\file   Jsonclass.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Json file parser header code
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once

#include "json.h"
#include <iostream>
#include  <fstream>
#include  "string"

class Jsonclass {

	
	


public:
	std::string  mPath;
	Json::Value mRoot;
	void ReadFile(std::string  pPath);
	void WriteFile(std::string pPath,Json::Value pRoot);
		
};
