//--------------------------------------------------//
// Filename: Triangle.cpp							//
//--------------------------------------------------//

#include "Triangle.h"

Triangle::Triangle()
{
	// Define a default triangle

	// Top left
	vertex[0].position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[0].texture = XMFLOAT2(0.0f, 1.0f);

	// Bottom left
	vertex[1].position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[1].texture = XMFLOAT2(0.0f, 0.0f);

	// Bottom right
	vertex[2].position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[2].texture = XMFLOAT2(1.0f, 0.0f);
}

Triangle::~Triangle()
{
}
