//--------------------------------------------------//
// Filename: Graphics.cpp							//
//--------------------------------------------------//

#include "Graphics.h"

// TODO - Remove colour shader code

Graphics::Graphics()
{
	direct3D = NULL;
	mainCamera = NULL;
	model = NULL;
	colourShader = NULL;
	textureShader = NULL;
	m_ParticleShader = NULL;
	m_ParticleSystem = NULL;
}

Graphics::Graphics(const Graphics& other)
{
}

Graphics::~Graphics()
{
}

bool Graphics::Init(int screenHeight, int screenWidth, HWND hwnd, Input* input_)
{
	bool result;

	input = input_;

	// Create the Direct3D object
	direct3D = new D3DClass;
	if (!direct3D)
	{
		return false;
	}

	// Initialise the Direct3D object
	result = direct3D->Init(screenHeight, screenWidth, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object
	mainCamera = new Camera;
	if (!mainCamera)
	{
		return false;
	}

	// Set the initial position of the camera
	mainCamera->SetPosition(0.0f, -2.0f, -10.0f);

	// Create the particle shader object
	/*m_ParticleShader = new ParticleShader;
	if (!m_ParticleShader)
	{
		return false;
	}*

	// Initialise the particle shader object
	/*result = m_ParticleShader->Initialize(direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}*/

	// Create the particle system object
	/*m_ParticleSystem = new ParticleSystem;
	if (!m_ParticleSystem)
	{
		return false;
	}*/

	// Initialise the particle system object
	/*result = m_ParticleSystem->Initialize(direct3D->GetDevice(), direct3D->GetDeviceContext(),  L"../DX12/Assets/cloudTex.tga");
	if (!result)
	{
		return false;
	}*/

	// Create the model object
	model = new Model;
	if (!model)
	{
		return false;
	}

	// Initialise the model object
	result = model->Init(direct3D->GetDevice(), direct3D->GetDeviceContext(), "../DX12/Assets/cloudTex.tga", 4, 6);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object
	textureShader = new TextureShader;
	if (!textureShader)
	{
		return false;
	}

	// Initialise the texture shader object
	result = textureShader->Init(direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	/*colourShader = new ColourShader;
	if (!colourShader)
	{
		return false;
	}*/

	// Initialise the color shader object.
	/*result = colourShader->Init(direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialise the color shader object.", L"Error", MB_OK);
		return false;
	}*/

	return true;
}

void Graphics::CleanUp()
{
	// Release the Direct3D object
	if (direct3D)
	{
		direct3D->CleanUp();
		delete direct3D;
		direct3D = NULL;
	}

	// Release the color shader object
	if (colourShader)
	{
		colourShader->Shutdown();
		delete colourShader;
		colourShader = NULL;
	}

	// Release the texture shader object
	if (textureShader)
	{
		textureShader->CleanUp();
		delete textureShader;
		textureShader = 0;
	}

	// Release the model object
	if (model)
	{
		model->CleanUp();
		delete model;
		model = NULL;
	}

	// Release the camera object
	if (mainCamera)
	{
		delete mainCamera;
		mainCamera = NULL;
	}

	// Release the particle system object
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	return;
}

bool Graphics::Update(float frameTime)
{
	bool result;

	// Run the frame processing for the particle system
	//m_ParticleSystem->Frame(frameTime, direct3D->GetDeviceContext());

	// Update the camera
	CameraUpdate(frameTime);

	// Render the graphics scene
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool Graphics::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene
	direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position
	mainCamera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects
	direct3D->GetWorldMatrix(worldMatrix);
	mainCamera->GetViewMatrix(viewMatrix);
	direct3D->GetProjectionMatrix(projectionMatrix);

	// Turn on alpha blending
	//direct3D->EnableAlphaBlending();

	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing
	/*m_ParticleSystem->Render(direct3D->GetDeviceContext());*/

	// Render the model using the particle shader
	/*result = m_ParticleShader->Render(direct3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_ParticleSystem->GetTexture());
	if (!result)
	{
		return false;
	}*/

	// Turn off alpha blending.
	//direct3D->DisableAlphaBlending();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing
	model->Render(direct3D->GetDeviceContext());

	// Render the model using the color shader
	/*result = colourShader->Render(direct3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}*/

	// Render the model using the texture shader
	result = textureShader->Render(direct3D->GetDeviceContext(), model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, model->GetTexture());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	direct3D->EndScene();

	return true;
}

void Graphics::CameraUpdate(float frameTime)
{
	mainCamera->UpdateFrameTime(frameTime);

	// Handle the input.
	if (input->IsKeyDown(0x57))			// W
	{
		// Forward
		mainCamera->MoveForward();
	}
	if (input->IsKeyDown(0x53))			// S
	{
		// Back
		mainCamera->MoveBackward();
	}
	if (input->IsKeyDown(0x41))			// A
	{
		// Strafe left
		mainCamera->StrafeLeft();
	}
	if (input->IsKeyDown(0x44))			// D
	{
		// Strafe right
		mainCamera->StrafeRight();
	}
	if (input->IsKeyDown(0x51))			// Q
	{
		// Down
		mainCamera->MoveDownward();
	}
	if (input->IsKeyDown(0x45))			// E
	{
		// Up
		mainCamera->MoveUpward();
	}
	if (input->IsKeyDown(VK_UP))
	{
		// Rotate up
		mainCamera->TurnUp();
	}
	if (input->IsKeyDown(VK_DOWN))
	{
		// Rotate down
		mainCamera->TurnDown();
	}
	if (input->IsKeyDown(VK_LEFT))
	{
		// Rotate left
		mainCamera->TurnLeft();
	}
	if (input->IsKeyDown(VK_RIGHT))
	{
		// Rotate right
		mainCamera->TurnRight();
	}
}