/******************************************************************************/
/*!
\file   Jsonclass.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Json file parser source code
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "JsonClass.h"

void Jsonclass::ReadFile(std::string  pPath)
{

	Json::Reader reader;
	std::ifstream readerStream(pPath.c_str(), std::ifstream::binary);

	bool isParssingSuccessful = reader.parse(readerStream, mRoot, false);

	if (isParssingSuccessful == false) {
		std::cerr << "Fail open file~~~ErrorMsg:" << reader.getFormattedErrorMessages() << std::endl;
	}
	
	readerStream.close();
}

void Jsonclass::WriteFile(std::string pPath, Json::Value pRoot)
{
	Json::Value confRoot;
	Json::StyledStreamWriter wirter;


	std::ofstream writeOfStream(pPath.c_str());

	wirter.write(writeOfStream, pRoot);
	
	writeOfStream.close();
	std::cerr << "Json File is Saved" << '\n';
}
