//--------------------------------------------------//
// Filename: Timer.h								//
//--------------------------------------------------//

#include "Timer.h"

Timer::Timer()
{
}

Timer::Timer(const Timer& other)
{
}

Timer::~Timer()
{
}

bool Timer::Init()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	if (frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	ticksPerMs = (float)(frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	return true;
}

void Timer::Update()
{
	INT64 currentTime;
	float timeDifference;


	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - startTime);

	frameTime = timeDifference / ticksPerMs;

	startTime = currentTime;

	return;
}

float Timer::GetTime()
{
	return frameTime;
}
