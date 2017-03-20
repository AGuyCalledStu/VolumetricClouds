//--------------------------------------------------//
// Filename: Font.h									//
//--------------------------------------------------//

#ifndef _FONT_H_
#define _FONT_H_

// Includes
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

// My Class Includes
#include "Texture.h"

// Namespaces
using namespace std;
using namespace DirectX;

class Font
{
private:

	// Struct types
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	Font();
	Font(const Font&);
	~Font();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	void CleanUp();

	ID3D11ShaderResourceView* GetTexture();

	void BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY);

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

private:
	FontType* font;
	Texture* texture;
};
#endif