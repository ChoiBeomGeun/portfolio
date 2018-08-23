/******************************************************************************/
/*!
\file   Timer.h
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Timer header file to get delta time
Static class to keep track of time
*/
/******************************************************************************/


#pragma once


#include <chrono>
namespace TE
{

	using namespace std::chrono;
	namespace {
		time_point<high_resolution_clock> prevTime;
		time_point<high_resolution_clock> currTime;
	}
	class Timer {

	private:

	public:
		static void Initialize(void) {
			prevTime = currTime =high_resolution_clock::now();
		
		};
		static float GetDelta(void) {
			currTime = high_resolution_clock::now();
			duration<float>delta(currTime - prevTime);

			prevTime = currTime;

			return delta.count();
		};

	};
}