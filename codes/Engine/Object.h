/******************************************************************************/
/*!
\file   Object.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Base Object class header file
Contains definition for the object class which each and every
entities in the game engine will be built upon.
*/
/******************************************************************************/





#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"
#include "ComponentType.h"
#include "Controller.h"
#include "Sprite.h"
#include "Body.h"
#include "Button.h"
#include "ObjectStyle.h"
#include "Camera.h"
#include  "TriggerC.h"
#include "Animation.h"
#include "Particles.h"


namespace TE {
	typedef unsigned int ObjectID;

	class Object
	{

	public:
		//Todo : friend class to ObjectFactory 
		friend class ObjectFactory;
		Object();
		~Object();
		//Init the object
		void Initialize();





		std::vector <Component*>mVcomponetList;

		// Properly destroy the object by delay destruction
		void Destroy();
		bool IsLoadingObject = false;
		template <typename ComponentType>
		void	 AddComponent();

		template <typename ComponentType>
		ComponentType*	GetComponent();
		

		template <typename ComponentType>
		bool HasComponent();
		ObjectID objID;	
		Objectstyle objectstyle;

	};


	template <typename ComponentType>
	bool Object::HasComponent()
	{
		for (auto inComponentList : mVcomponetList)
		{

			if (typeid(*inComponentList).name() == typeid(ComponentType).name())
				return true;
		}
		return false;

	}



	template<typename ComponentType>
	void Object::AddComponent()
	{
		if (HasComponent<ComponentType>()) {
			return;
		}
		ComponentType * temp = new ComponentType();
		dynamic_cast<Component*>(temp)->SetOwner(this);
		this->mVcomponetList.push_back(temp);



	}

	template<typename ComponentType>
	ComponentType* Object::GetComponent()
	{
		for(auto inComponentList : mVcomponetList)
		{

			if (typeid(*inComponentList).name() == typeid(ComponentType).name())
				return dynamic_cast<ComponentType*>(inComponentList);
		}
		return nullptr;

	}
}