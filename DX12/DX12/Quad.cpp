//--------------------------------------------------//
// Filename: Quad.cpp								//
//--------------------------------------------------//

#include "Quad.h"

Quad::Quad()
{
	// Define a default quad

	// Triangle 1
	// Top left
	triangle[0].vertex[0].position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	triangle[0].vertex[0].texture = XMFLOAT2(0.0f, 1.0f);

	// Bottom left
	triangle[0].vertex[1].position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	triangle[0].vertex[1].texture = XMFLOAT2(0.0f, 0.0f);

	// Bottom right
	triangle[0].vertex[2].position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	triangle[0].vertex[2].texture = XMFLOAT2(1.0f, 0.0f);

	// Triangle 2
	// Bottom right
	triangle[1].vertex[0].position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	triangle[1].vertex[0].texture = XMFLOAT2(1.0f, 0.0f);

	// Top right
	triangle[1].vertex[1].position = XMFLOAT3(0.5f, 0.5f, 0.0f);
	triangle[1].vertex[1].texture = XMFLOAT2(1.0f, 1.0f);

	// Top left
	triangle[1].vertex[2].position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	triangle[1].vertex[2].texture = XMFLOAT2(0.0f, 1.0f);
}

Quad::~Quad()
{
}
