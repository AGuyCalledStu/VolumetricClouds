//--------------------------------------------------//
// Filename: System.h								//
//--------------------------------------------------//

#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

// Pre-Processing Directives
#define WIN32_LEAN_AND_MEAN

// Includes
#include <Windows.h>

// My Class Includes
#include "Input.h"
#include "Graphics.h"
#include "Timer.h"
#include "Framerate.h"
#include "_CPU.h"


class System
{
public:
	System();
	System(const System&);
	~System();

	bool Init();
	void CleanUp();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Update();
	void InitWindows(int&, int&);
	void ShutdownWindows();

	LPCWSTR applicationName;
	HINSTANCE hInstance;
	HWND hwnd;

	Input* input;
	Graphics* graphics;
	Timer* timer;
	Framerate* framerate;
	_CPU* _cpu;
};

// Function Prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Globals
static System* ApplicationHandle = NULL;

#endif
