//--------------------------------------------------//
// Filename: Voxel.cpp								//
//--------------------------------------------------//

#include "Voxel.h"

Voxel::Voxel()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexCount = 8;
	DefineCube();
}

Voxel::~Voxel()
{
}

void Voxel::DefineCube()
{
	// Define a unit cube
	// Lower quad
	vertex[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[2].position = XMFLOAT3(1.0f, 0.0f, 1.0f);
	vertex[3].position = XMFLOAT3(1.0f, 0.0f, 0.0f);

	// Upper quad
	vertex[4].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[5].position = XMFLOAT3(0.0f, 1.0f, 1.0f);
	vertex[6].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertex[7].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
}