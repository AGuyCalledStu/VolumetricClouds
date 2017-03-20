//--------------------------------------------------//
// Filename: FontShader.h							//
//--------------------------------------------------//

#ifndef _FONTSHADER_H_
#define _FONTSHADER_H_

// Includes
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>

// Namespaces
using namespace std;
using namespace DirectX;

class FontShader
{
private:
	// Struct types
	struct ConstantBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct PixelBufferType
	{
		XMFLOAT4 pixelColour;
	};

public:
	FontShader();
	FontShader(const FontShader&);
	~FontShader();

	bool Init(ID3D11Device*, HWND);
	void CleanUp();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);

private:
	bool InitShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void CleanUpShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* constantBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* pixelBuffer;
};
#endif