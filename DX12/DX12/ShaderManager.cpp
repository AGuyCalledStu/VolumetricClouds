//--------------------------------------------------//
// Filename: ShaderManager.cpp						//
//--------------------------------------------------//

#include "ShaderManager.h"

// TODO - Follow RasterTek ShaderManager tutorial once this is neccessary

ShaderManager::ShaderManager()
{
	// Initialise all shader objects to NULL
}

ShaderManager::ShaderManager(const ShaderManager& other)
{
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::Init(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Create shader object

	// Initialise shader object

	return true;
}

void ShaderManager::Shutdown()
{
	// Release any shader objects here

	return;
}