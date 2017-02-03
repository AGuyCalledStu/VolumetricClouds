//--------------------------------------------------//
// Filename: Quad.h									//
//--------------------------------------------------//

#ifndef _QUAD_H_
#define _QUAD_H_

// Includes
#include "Vertex.h"

// Namespaces
using namespace DirectX;

class Quad
{
public:
	Quad();
	~Quad();

	Vertex vertex[4];

	void Translate(float x, float y, float z, float w);
	void Rotate(float x, float y, float z, float w);
	void Scale(float x, float y, float z, float w);
};

#endif