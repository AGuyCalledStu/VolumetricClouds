//--------------------------------------------------//
// Filename: Vertex.h								//
//--------------------------------------------------//

#ifndef _VERTEX_H_
#define _VERTEX_H_

// Includes
#include <d3d11.h>
#include <DirectXMath.h>

// Namespaces
using namespace DirectX;

class Vertex
{
public:
	Vertex();
	~Vertex();

	XMFLOAT3 position;
	//XMFLOAT2 texture;
	//XMFLOAT3 normal;
	XMFLOAT4 colour;
	int index;
};
#endif