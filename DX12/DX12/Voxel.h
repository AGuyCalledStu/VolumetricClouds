//--------------------------------------------------//
// Filename: Voxel.h								//
//--------------------------------------------------//

#ifndef _MODEL_H_
#define _MODEL_H_

// Includes
#include "Quad.h"

// Namespaces
using namespace DirectX;

class Voxel
{
public:
	Voxel();
	~Voxel();

private:
	XMFLOAT3 centre;
	void DefineCube();
};

#endif