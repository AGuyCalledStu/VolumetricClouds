//--------------------------------------------------//
// Filename: System.cpp								//
//--------------------------------------------------//

#include "System.h"

System::System()
{
	input = NULL;
	graphics = NULL;
	timer = NULL;
}

System::System(const System& other)
{
}

System::~System()
{
}

bool System::Init()
{
	int screenHeight, screenWidth;
	bool result;

	// Initialise the width and height of the screen to zero before sending the variables into the function
	screenHeight = 0;
	screenWidth = 0;

	// Initialise the windows api
	InitWindows(screenHeight, screenWidth);

	// Create the input object, this object will be used to handle reading keyboard input
	input = new Input;
	if (!input)
	{
		return false;
	}

	// Initialise the input object
	input->Init();

	// Create the graphics object, this object will handle rendering all the graphics for this application
	graphics = new Graphics;
	if (!graphics)
	{
		return false;
	}

	// Initialise the graphics object
	result = graphics->Init(screenHeight, screenWidth, hwnd, input);
	if (!result)
	{
		return false;
	}

	// Create the timer object.
	timer = new Timer;
	if (!timer)
	{
		return false;
	}

	// Initialise the timer object.
	result = timer->Init();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void System::CleanUp()
{
	// Release the graphics object
	if (graphics)
	{
		graphics->CleanUp();
		delete graphics;
		graphics = NULL;
	}

	// Release the input object
	if (input)
	{
		delete input;
		input = NULL;
	}

	// Release the timer object
	if (timer)
	{
		delete timer;
		timer = NULL;
	}

	// Shutdown the window
	ShutdownWindows();

	return;
}

void System::Run()
{
	MSG msg;
	bool running, result;

	// Initialise the message structure
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user
	running = true;
	while (running)
	{
		// Handle the windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out
		if (msg.message == WM_QUIT)
		{
			running = false;
		}
		else
		{
			// Otherwise do the frame processing
			result = Update();
			if (!result)
			{
				running = false;
			}
		}
	}

	return;
}

bool System::Update()
{
	bool result;

	// Update the system stats.
	timer->Update();

	// Check if the user pressed the escape key
	if (input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// Do the frame processing for the graphics object
	result = graphics->Update(timer->GetTime());
	if (!result)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK System::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	
	switch (umsg)
	{		
		// Check if a key down has been pressed on the keyboard
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state
			input->KeyDown((unsigned int)wparam);
			return 0;
		}
		// Check if a key has been released on the keyboard
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key
			input->KeyUp((unsigned int)wparam);
			return 0;
		}
		// Any other messages send to the default message handler as our application won't make use of them
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

void System::InitWindows(int& screenHeight, int& screenWidth)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get an external pointer to this object
	ApplicationHandle = this;

	// Get the instance of this application
	hInstance = GetModuleHandle(NULL);

	// Give the application a name
	applicationName = L"DX11 Clouds";

	// Setup the windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		
		// Change the display settings to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner
		posX = 0;
		posY = 0;
	}
	else if (!FULL_SCREEN)
	{
		// If windowed then set it to 1280 x 720 resolution
		screenWidth = 1280;
		screenHeight = 720;

		// Place the window in the middle of the screen
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
							applicationName,			// Name of the window class
							applicationName,			// Window title
							WS_OVERLAPPEDWINDOW,		// Window style
							posX, posY,					// Window position
							screenWidth, screenHeight,	// Window size
							NULL,						// We have no parent window - NULL
							NULL,						// We aren't using menus - NULL
							hInstance,					// Application handle
							NULL);						// Used with multiple windows - NULL

	// Bring the window up on the screen and set it as main focus
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Hide the mouse cursor
	// ShowCursor(false);

	return;
}

void System::ShutdownWindows()
{
	// Show the mouse cursor
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window
	DestroyWindow(hwnd);
	hwnd = NULL;

	// Remove the application instance
	UnregisterClass(applicationName, hInstance);
	hInstance = NULL;

	// Release the pointer to this class
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		// Check if the window is being closed
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		// All other messages pass to the message handler in the system class
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}