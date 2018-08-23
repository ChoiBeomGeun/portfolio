/******************************************************************************/
/*!
\file   Input.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2018/05/29

Keyboard and mouse Input header file
Uses SDL2 for interpreting input and checks key status

*/
/******************************************************************************/

#pragma once
#include <SDL.h>
#include  "Application.h"
#include <bitset>
#include <glm/glm.hpp>

namespace TE {

	class Input {
	public:
		//Input();
		//~Input();
		static void Initialize();
		static void Reset(void);
		//Sets pressed, triggered, released or unpressed status of a key
		static void SetKeyPressed(SDL_Scancode key, SDL_EventType keyStatus);
		static void SetMousePressed(int MouseButton, SDL_EventType MouseStatus);
		static void MouseReact(glm::vec3  position, glm::vec3  scale);
		//Check if a specific is pressed, triggered or released
		static bool IsPressed(SDL_Scancode key);
		static bool IsTriggered(SDL_Scancode key);
		static bool IsReleased(SDL_Scancode key);

		static bool IsMousePressed(int mouse);
		static bool IsMouseTriggered(int mouse);
		static bool IsMouseReleased(int mouse);

		static bool IsAnyPressed(void);
		static bool IsAnyTriggered(void);
		static bool IsAnyReleased(void);

		static bool IsMouseDown;
		static bool IsMouseUp;
	};




}

