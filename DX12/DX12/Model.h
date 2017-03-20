//--------------------------------------------------//
// Filename: Model.h								//
//--------------------------------------------------//

#ifndef _MODEL_H_
#define _MODEL_H_

// Includes
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

// My Class Includes
#include "Texture.h"
#include "Vertex.h"
#include "PerlinNoise.h"
#include "ppm.h"
#include "Voxel.h"

// Namespaces
using namespace DirectX;
using namespace std;

class Model
{
private:

	struct ModelType
	{
		float vx, vy, vz;		// Vertices
		float tu, tv;			// Texture coordinates
		float nx, ny, nz;		// Normals
		float cr, cg, cb, ca;	// Colours
	};

	struct InstanceType
	{
		XMFLOAT3 position;		// Local position of instance
		XMFLOAT4 colour;
	};

public:
	Model();
	Model(const Model&);
	~Model();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	void CleanUp();
	void Render(ID3D11DeviceContext*);

	int GetVertexCount();
	int GetInstanceCount();
	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

	bool LoadVoxel();

	void InitPerlin();

	ID3D11Buffer *vertexBuffer, *indexBuffer, *instanceBuffer;
	int vertexCount, indexCount, instanceCount;

	Texture* texture;

	Voxel* voxel;

	ModelType* model;

	// Generation variations
	unsigned int width, height, depth;
	unsigned int seed;
	ppm* image;
	PerlinNoise* perlinNoise;

	double noiseOutput;
};
#endif