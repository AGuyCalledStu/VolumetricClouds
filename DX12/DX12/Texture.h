//--------------------------------------------------//
// Filename: Texture.h								//
//--------------------------------------------------//

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

// Includes
#include <d3d11.h>
#include <stdio.h>

class Texture
{
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	Texture();
	Texture(const Texture&);
	~Texture();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, char*);
	void CleanUp();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool LoadTarga(char*, int&, int&);

	unsigned char* targaData;
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* textureView;
};
#endif