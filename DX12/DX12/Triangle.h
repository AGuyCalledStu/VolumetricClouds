//--------------------------------------------------//
// Filename: Triangle.h								//
//--------------------------------------------------//

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

// Includes
#include "Vertex.h"

// Namespaces
using namespace DirectX;

class Triangle
{
public:
	Triangle();
	~Triangle();

	Vertex vertex[3];

	void Translate(float x, float y, float z, float w);
	void Rotate(float x, float y, float z, float w);
	void Scale(float x, float y, float z, float w);
};

#endif