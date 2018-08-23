/******************************************************************************/
/*!
\file   Transform.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Transform
*/
/******************************************************************************/

#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "TUMath.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Application.h"


namespace TE {
	class Transform : public Component {

	public:
		Transform() : Component(ComponentType::CT_TRANSFORM)
		{
			position = glm::vec3(0, 0, 0);
			rotation = glm::vec3(0, 0, 0);
			scale = glm::vec3(1, 1, 1);
			angle = 0.0f;
			u_v = glm::vec2(1.f,1.f);
		}
		glm::vec3 GetPosition() { return position; }
		glm::vec3 GetRotation() { return rotation; }
		glm::vec3 GetScale() { return scale; }
		float GetRotationZ() { return angle; }

		void SetRotationZ(float zangle) { angle = TUMath::DegreeToRadian(zangle); }
		void SetPosition(const glm::vec3& pos) { position = pos; }
		void SetRotation(const glm::vec3& Rot) { rotation = Rot; }
		void SetScale(const glm::vec3& Scale) { scale = Scale; }
		
		float angle;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec2 u_v;
	private:

	};




}