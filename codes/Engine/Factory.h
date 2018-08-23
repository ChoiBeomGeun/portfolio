/******************************************************************************/
/*!
\file   Factory.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2018/3/29

OvjectFactory handles the creation , managment , and
destruction of all Objects
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#pragma once
#include "System.h"
#include "Object.h"
#include <map>
#include <glm/glm.hpp>
#include "Archetype.h"

namespace TE {
	struct ReplayerInfo {
		glm::vec3 Pos = { 0,0,0 };
		bool mouseinfo = 0;
		float aniframe =0;
		float anitime = 0;
	};
	class ObjectFactory : public Systems {
	public:


		ObjectFactory();
		~ObjectFactory();
		
		void Initialize() override;

		void Update(float dt) override;
		//Add an object to the destroy list for delay destruction
		void Destroy(Object *);

		//For the shutdown the Factory
		void DestroyAllObjects();
		//ID the Object and store it in the object list(map)
		void IDGameObject(Object* gameObject);
		int GetObjectID(int objectID);
		//Return an object with specific ID
		Object* GetObjectwID (ObjectID id);
		Object * CreateWall(const glm::vec3 & pos, const glm::vec3 & scale);
	
		Object * CreateEmptyObject();
		//Showing how to create an object through hardcode
		//Todo : when applying data driven methods, use this as blueprint
		void CreateBoundary(void);
	
		Object * CreateArchetype(Archetype path);
		Object * TE::ObjectFactory::CreateHUD(const glm::vec3 & pos, const glm::vec3 & scale);
		//used to incremetallly  generate unique ID
		ObjectID LastObjectID;
		ObjectID BodyID;
		Object * GetPlayer(void);
		Object * GetClearZone(void);
		Object * LeftBoundary(void);
		Object * RightBoundary(void);
		Object * UpBoundary(void);
		Object * DownBoundary(void);
		Object * GamePlayer = nullptr;
		unsigned int GetAllObjectNumbers(void);
		//Map of Objects to their IDs used for safe referencing
		std::map<ObjectID, Object*> ObjectIDMap;
                std::vector<unsigned int> BodyNum;
		//List of objects to be deleted
		//To prevent problems of early or multi call of object's destruction
		std::vector<Object *> ObjectsToBeDeleted;
		
	};
	extern ObjectFactory * FACTORY;

}