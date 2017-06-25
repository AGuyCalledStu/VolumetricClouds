#include "Framerate.h"

Framerate::Framerate()
{
}

Framerate::Framerate(const Framerate& other)
{
}

Framerate::~Framerate()
{
}

void Framerate::Init()
{
	framerate = 0;
	count = 0;
	startTime = timer.GetTime();
}

void Framerate::Frame()
{
	count++;

	if (timer.GetTime() >= (startTime + 1000))
	{
		framerate = count;
		count = 0;

		startTime = timer.GetTime();
	}
}

int Framerate::GetFramerate()
{
	return framerate;
}