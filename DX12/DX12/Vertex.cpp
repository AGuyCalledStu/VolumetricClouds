//--------------------------------------------------//
// Filename: Vertex.cpp								//
//--------------------------------------------------//

#include "Vertex.h"

Vertex::Vertex()
{
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//texture = XMFLOAT2(0.0f, 0.0f);
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Vertex::~Vertex()
{
}