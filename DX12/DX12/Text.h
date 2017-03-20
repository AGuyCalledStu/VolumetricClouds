//--------------------------------------------------//
// Filename: Text.h									//
//--------------------------------------------------//

#ifndef _TEXT_H_
#define _TEXT_H_

// My Includes
#include "Font.h"
#include "FontShader.h"

class Text
{
private:
	// Struct Types
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	Text();
	Text(const Text&);
	~Text();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, XMMATRIX);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, XMMATRIX, XMMATRIX);

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, XMMATRIX, XMMATRIX);

private:
	Font* font;
	FontShader* fontShader;
	int m_screenWidth, screenHeight;
	XMMATRIX baseViewMatrix;

	SentenceType* sentence1;
	SentenceType* sentence2;
};
#endif