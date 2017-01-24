//--------------------------------------------------//
// Framework adapated from rasterek.com				//
// Application developed by Stuart McEwan			//
// DX11												//
//--------------------------------------------------//

//--------------------------------------------------//
// Filename: main.cpp								//
//--------------------------------------------------//

#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	System* system;
	bool result;

	// Create the system object
	system = new System;
	if (!system)
	{
		return 0;
	}

	// Initialise and run the system object
	result = system->Init();
	if (result)
	{
		system->Run();
	}

	// Shutdown and release the system object
	system->CleanUp();
	delete system;
	system = NULL;

	return 0;
}