#include "Timer.h"

Engine::Timer::Timer()
{
	cntsPerSec = prevTimeStamp = currTimeStamp = 0;
	secsPerCnt = dt = soon = 0.0f;
	lastTime = currentTime = 0;
}

Engine::Timer::~Timer()
{}

Engine::Timer *Engine::Timer::instance()
{
	static Timer timer;
	return &timer;
}

void Engine::Timer::init()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	secsPerCnt = 1.0f / (float)cntsPerSec;

	QueryPerformanceFrequency((LARGE_INTEGER*)&prevTimeStamp);

	lastTime = timeGetTime();
	

}

void Engine::Timer::update()
{
	currTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
	dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;
	prevTimeStamp = currTimeStamp;
	soon = (float)(currTimeStamp + 1000/60);
}

float Engine::Timer::getDT()
{
	return dt;
}

float Engine::Timer::getSoon()
{
	return soon;
}

