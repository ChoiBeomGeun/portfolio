/******************************************************************************/
/*!
\file   Object.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Base Object class source file
*/
/******************************************************************************/


#include "Object.h"
#include "DebugUtil.h"

using namespace TE;

Object::Object()
{
}
Object::~Object()
{

	for (auto inComponentList : mVcomponetList)
	{
 		delete inComponentList;
	
	}
	mVcomponetList.clear();


	//Todo : delete ALL componenets

}	





void Object::Initialize()
{
	for (auto components : this->mVcomponetList)
	{
		components->Initialize();
	}
	//Todo : Init all components


}



//Signal the object factory for delay destruction
void Object::Destroy() {




}
