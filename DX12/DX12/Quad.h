//--------------------------------------------------//
// Filename: Quad.h									//
//--------------------------------------------------//

#ifndef _QUAD_H_
#define _QUAD_H_

// Includes
#include "Triangle.h"

// Namespaces
using namespace DirectX;

class Quad
{
public:
	Quad();
	~Quad();

	Triangle triangle[2];

	void Translate(float x, float y, float z, float w);
	void Rotate(float x, float y, float z, float w);
	void Scale(float x, float y, float z, float w);
};

#endif