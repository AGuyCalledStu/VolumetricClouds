//--------------------------------------------------//
// Filename: Voxel.h								//
//--------------------------------------------------//

#ifndef _VOXEL_H_
#define _VOXEL_H_

// Includes
#include "Vertex.h"

// Namespaces
using namespace DirectX;

class Voxel
{
public:
	Voxel();
	~Voxel();
	int vertexCount;

private:
	XMFLOAT3 position;
	Vertex vertex[8];
	void DefineCube();
};

#endif