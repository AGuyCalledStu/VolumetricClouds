//--------------------------------------------------//
// Filename: Timer.h								//
//--------------------------------------------------//

#ifndef _TIMER_H_
#define _TIMER_H_

// Includes
#include <Windows.h>

class Timer
{
public:
	Timer();
	Timer(const Timer&);
	~Timer();

	bool Init();
	void Update();

	float GetTime();

private:
	INT64 frequency;
	float ticksPerMs;
	INT64 startTime;
	float frameTime;
};
#endif