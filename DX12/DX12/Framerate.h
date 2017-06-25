#ifndef _FRAMERATE_H_
#define _FRAMERATE_H_

// Linking
#pragma comment(lib, "winmm.lib")

// Includes
#include <windows.h>
#include <mmsystem.h>

// My Includes
#include "Timer.h"

class Framerate
{
public:
	Framerate();
	Framerate(const Framerate&);
	~Framerate();

	void Init();
	void Frame();
	int GetFramerate();

private:
	int framerate, count;
	unsigned long startTime;
	Timer timer;
};
#endif