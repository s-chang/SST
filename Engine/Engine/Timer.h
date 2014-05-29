/**
Written by:  Smyth Chang
Description: The Timer class returns the change in time between the previous loop and the current one.
*/

#pragma once
#include <Windows.h>

namespace Engine
{
	class Timer
	{
	private:
		__int64 cntsPerSec, prevTimeStamp, currTimeStamp;
		float secsPerCnt, dt, soon;
		unsigned int lastTime, currentTime;

		Timer();

	public:
		~Timer();

		/**
		Name:		instance
		Parameters: none
		Return:		Timer
		Description: Returns the only instance of timer.
		*/
		static Timer *instance();

		/**
		Name:		init
		Parameters: none
		Return:		void
		Description: initializes variables
		*/
		void init();

		/**
		Name:		update
		Parameters: none
		Return:		void
		Description: updates the timer
		*/
		void update();

		/**
		Name:		getDT
		Parameters: none
		Return:		float
		Description: Returns the change in time from the previous update and the current update
		*/
		float getDT();

		/**
		Name:		getSoon
		Parameters: none
		Return:		float
		Description: 
		*/
		float getSoon();

	};
};