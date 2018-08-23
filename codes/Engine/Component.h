/******************************************************************************/
/*!
\file   Component.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

This calss contains definition for component class, which
gives identity to every Object in the game
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/



#pragma once
#include "ComponentType.h"
namespace TE {
	//Forward Declaration of Object Class
	 class  Object;
	class Component

	{
	public:
		friend class Object;
		//todo : friend class Object;
		//Object will init all components
		virtual void Initialize() {};

		Object * GetOwner() const { return pOwner; }
		void SetOwner(Object * owner) { pOwner = owner; }
		ComponentType GetType(){return cType;}
		virtual ~Component() {  };
		Component(ComponentType type) : cType(type) {}
		Object * pOwner;
		ComponentType cType;
	};




}