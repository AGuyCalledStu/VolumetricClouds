//--------------------------------------------------//
// Filename: Model.cpp								//
//--------------------------------------------------//

#include "Model.h"

Model::Model()
{
	vertexBuffer = NULL;
	indexBuffer = NULL;
	instanceBuffer = NULL;
	texture = NULL;
	model = NULL;
}

Model::Model(const Model& other)
{
}

Model::~Model()
{
}

bool Model::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* modelFilename, char* textureFilename)
{
	bool result;

	InitPerlin();

	// Load in the model data
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialise the vertex and index buffers
	result = InitBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	/*result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}*/

	return true;
}

void Model::CleanUp()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers
	ShutdownBuffers();

	// Release the model data
	ReleaseModel();

	return;
}

void Model::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing
	RenderBuffers(deviceContext);

	return;
}

int Model::GetIndexCount()
{
	return indexCount;
}

int Model::GetVertexCount()
{
	return vertexCount;
}

int Model::GetInstanceCount()
{
	return instanceCount;
}

ID3D11ShaderResourceView* Model::GetTexture()
{
	return texture->GetTexture();
}

bool Model::InitBuffers(ID3D11Device* device)
{
	Vertex* vertices;
	unsigned long* indices;
	InstanceType* instances;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, instanceData;
	HRESULT result;

	// Set the number of vertices in the vertex array
	//vertexCount = 4;

	// Set the number of indices in the index array
	//indexCount = 6;

	// Create the vertex array
	vertices = new Vertex[vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array
	indices = new unsigned long[indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(model[i].vx, model[i].vy, model[i].vz);
		//vertices[i].texture = XMFLOAT2(model[i].tu, model[i].tv);
		vertices[i].colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertices[i].normal = XMFLOAT3(model[i].nx, model[i].ny, model[i].nz);

		indices[i] = i;
	}

	// Load the vertex array with data
	/*vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left
	vertices[0].texture = XMFLOAT2(0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // Top left
	vertices[1].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[2].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top right
	vertices[2].texture = XMFLOAT2(1.0f, 0.0f);

	vertices[3].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right
	vertices[3].texture = XMFLOAT2(1.0f, 1.0f);*/

	// Load the index array with data
	/*indices[0] = 0;  // Bottom left
	indices[1] = 1;  // Top left
	indices[2] = 2;  // Top right

	indices[3] = 2;  // Top right
	indices[4] = 3;  // Bottom right
	indices[5] = 0;  // Bottom left*/

	// Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	// --- Instancing --- //
	
	// Set the number of instances in the array
	instanceCount = width * height * depth;

	// Create the instance array
	instances = new InstanceType[instanceCount];
	if (!instances)
	{
		return false;
	}

	// Load the instance array with data
	for (int iCount = 0; iCount < instanceCount;)
	{
		int i = 0;
		int j = 0;
		int k = 0;

		for (i = 0; i < width; i++)
		{
			for (j = 0; j < height; j++)
			{
				for (k = 0; k < depth; k++)
				{
					noiseOutput = perlinNoise->noise((double)i/6, (double)j/6, (double)k/6);
					if (noiseOutput >= 0.7)
					{
						instances[iCount].position = XMFLOAT3(i, j, k);
						instances[iCount].colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
					}
					iCount++;
				}
			}
		}
	}

	// Set up the description of the instance buffer
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.
	delete[] instances;
	instances = 0;

	return true;
}

void Model::ShutdownBuffers()
{
	// Release the index buffer
	if (indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = 0;
	}

	// Release the vertex buffer
	if (vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = 0;
	}

	// Release the instance buffer.
	if (instanceBuffer)
	{
		instanceBuffer->Release();
		instanceBuffer = 0;
	}

	return;
}

void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride[2];
	unsigned int offset[2];
	ID3D11Buffer* bufferPointer[2];

	// Set buffer strides
	stride[0] = sizeof(Vertex);
	stride[1] = sizeof(InstanceType);

	// Set buffer offsets
	offset[0] = NULL;
	offset[1] = NULL;

	// Set the array of pointers to the vertice and instance buffers
	bufferPointer[0] = vertexBuffer;
	bufferPointer[1] = instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered
	deviceContext->IASetVertexBuffers(0, 2, bufferPointer, stride, offset);

	// Set the index buffer to active in the input assembler so it can be rendered
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool Model::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;

	// Create the texture object
	texture = new Texture;
	if (!texture)
	{
		return false;
	}

	// initialise the texture object
	result = texture->Init(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void Model::ReleaseTexture()
{
	// Release the texture object.
	if (texture)
	{
		texture->CleanUp();
		delete texture;
		texture = 0;
	}

	return;
}

bool Model::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	
	// Open the model file
	fin.open(filename);

	// If it could not open the file then exit
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> vertexCount;

	// Set the number of indices to be the same as the vertex count.
	indexCount = vertexCount;

	// Create the model using the vertex count that was read in.
	model = new ModelType[vertexCount];
	if (!model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (int i = 0; i < vertexCount; i++)
	{
		fin >> model[i].vx >> model[i].vy >> model[i].vz;
		fin >> model[i].tu >> model[i].tv;
		fin >> model[i].nx >> model[i].ny >> model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}

void Model::ReleaseModel()
{
	if (model)
	{
		delete[] model;
		model = 0;
	}

	return;
}

void Model::InitPerlin()
{
	// Dimensions of 3D Perlin image
	width = 50;
	height = 3;
	depth = 50;

	// New image using width and depth
	image = new ppm(width, depth);

	// Generate a seed between 0 and the max value of and unsigned int
	seed = rand() % UINT_MAX;

	// New perlin noise object using seed
	perlinNoise = new PerlinNoise(seed);
}

bool Model::LoadVoxel()
{
	unsigned long* indices;

	int vertexCount = voxel->vertexCount;
	int indexCount = 36;

	// Create the index array
	indices = new unsigned long[indexCount];
	if (!indices)
	{
		return false;
	}

	//indices[0]
}