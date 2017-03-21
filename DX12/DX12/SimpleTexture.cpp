#include "SimpleTexture.h"

SimpleTexture::SimpleTexture()
{
	texture = NULL;
}

SimpleTexture::SimpleTexture(const SimpleTexture& other)
{
}

SimpleTexture::~SimpleTexture()
{
}

bool SimpleTexture::Init(ID3D11Device* device, WCHAR* filename)
{
	bool result;

	// Load the texture in
	//result = CreateDDSTexture
	return false;
}