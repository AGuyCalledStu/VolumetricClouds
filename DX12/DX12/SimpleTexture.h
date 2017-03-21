#ifndef _SIMPLE_TEXTURE_H_
#define _SIMPLE_TEXTURE_H_

// Includes
#include <d3d11.h>

class SimpleTexture
{
public:
	SimpleTexture();
	SimpleTexture(const SimpleTexture&);
	~SimpleTexture();

	bool Init(ID3D11Device*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* texture;
};
#endif