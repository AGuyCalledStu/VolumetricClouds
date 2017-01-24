//--------------------------------------------------//
// Filename: Model.h								//
//--------------------------------------------------//

#ifndef _MODEL_H_
#define _MODEL_H_

// Includes
#include <d3d11.h>
#include <DirectXMath.h>

// My Class Includes
#include "Texture.h"
#include "Vertex.h"

// Namespaces
using namespace DirectX;

class Model
{
private:
	/*struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};*/

public:
	Model();
	Model(const Model&);
	~Model();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, char*, int, int);
	void CleanUp();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int vertexCount, indexCount;

	Texture* texture;
};
#endif