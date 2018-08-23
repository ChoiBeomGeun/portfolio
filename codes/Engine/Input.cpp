/******************************************************************************/
/*!
\file   Input.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2018/03/29

Keyboard and mouse Input source file
Uses SDL2 for interpreting input and checks key status

*/
/******************************************************************************/





#include "Input.h"
#include "DebugUtil.h"

using namespace TE;
#define SDL_NUM_MOUSE 4
namespace {

	std::bitset<SDL_NUM_SCANCODES> s_pressed;//container of key pressed this frame

	std::bitset<SDL_NUM_SCANCODES> s_triggered;//container of key pressed this frame

	std::bitset<SDL_NUM_SCANCODES> s_released;//container of key pressed this frame

	std::bitset<SDL_NUM_MOUSE> s_mousePressed;

	std::bitset<SDL_NUM_MOUSE> s_mouseTriggered;

	std::bitset<SDL_NUM_MOUSE> s_mouseReleased;

	bool B_inputcheck = false;
	bool B_IsKeyDown = false;

	bool IsMouseDown = false;
	bool IsMouseUp = false;
}

void Input::Initialize() {
	s_released.reset();
	s_pressed.reset();
	s_triggered.reset();

	s_mouseReleased.reset();
	s_mousePressed.reset();
	s_mouseTriggered.reset();
}

void Input::SetKeyPressed(SDL_Scancode key, SDL_EventType keyStatus) {
	DEBUG_ASSERT(key < SDL_SCANCODE_UNKNOWN || key >SDL_NUM_SCANCODES, "Ay Yo crazy? Invaild key input");

	if (keyStatus == SDL_KEYDOWN) // if the key is pressed
	{
		s_pressed.set(key);
		if (!B_inputcheck)
			s_triggered.set(key);
		B_inputcheck = true;
	}
	else if (keyStatus == SDL_KEYUP)
	{

		B_inputcheck = false;
		s_released.set(key);
		s_pressed.reset(key);
	}

}

void Input::SetMousePressed(int MouseButton, SDL_EventType MouseStatus)
{
	if (MouseStatus == SDL_MOUSEBUTTONDOWN)
	{
		s_mousePressed.set(MouseButton);

		s_mouseTriggered[MouseButton] = true;

		IsMouseDown = true;

		IsMouseUp = false;
	}
	else if (MouseStatus == SDL_MOUSEBUTTONUP)
	{
		s_mouseTriggered[MouseButton] = false;
		s_mouseReleased.set(MouseButton);
		s_mousePressed.reset(MouseButton);

		IsMouseDown = false;

		IsMouseUp = true;
	}

}

void Input::MouseReact(glm::vec3   /*position*/, glm::vec3  /*scale*/)
{
	//glm::vec3  converted = APP->ConvertToNDC(APP->mousePos);


	//	if (((converted.x > position.x - scale.x*0.5f) && (converted.x < position.x + scale.x)) && ((converted.y > position.y - scale.y*0.5f) && (converted.y < position.y + scale.y)))
	//		;



}

void Input::Reset(void) {
	s_released.reset();
	s_triggered.reset();
	
	s_mouseReleased.reset();
	s_mouseTriggered.reset();

	IsMouseDown = false;
	IsMouseUp = false;
}


bool Input::IsPressed(SDL_Scancode key) {

	return s_pressed[key];
}


bool Input::IsTriggered(SDL_Scancode key) {

	return s_triggered[key];
}

bool Input::IsReleased(SDL_Scancode key) {

	return s_released[key];
}

bool Input::IsMousePressed(int mouse)
{
	return s_mousePressed[mouse];
}

bool Input::IsMouseTriggered(int mouse)
{
	return s_mouseTriggered[mouse];
}

bool Input::IsMouseReleased(int mouse)
{
	return s_mouseReleased[mouse];
}

bool Input::IsAnyPressed(void) {
	return s_pressed.any();
}

bool Input::IsAnyTriggered(void) {
	return s_triggered.any();
}

bool Input::IsAnyReleased(void) {
	return s_released.any();
}