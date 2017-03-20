//--------------------------------------------------//
// Filename: Font.cpp								//
//--------------------------------------------------//

#include "Font.h"

Font::Font()
{
	font = NULL;
	texture = NULL;
}

Font::Font(const Font& other)
{
}

Font::~Font()
{
}

bool Font::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* fontFilename, char* textureFilename)
{
	bool result;

	// Load in the text file containing the font data
	result = LoadFontData(fontFilename);
	if (!result)
	{
		return false;
	}

	// Load the texture that has the font characters on it
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void Font::CleanUp()
{
	// Release the font texture
	ReleaseTexture();

	// Release the font data
	ReleaseFontData();
}

bool Font::LoadFontData(char* filename)
{
	ifstream fin;
	int i;
	char temp;

	// Create the font spacing buffer
	font = new FontType[95];
	if(!font)
	{
		return false;
	}

	// Read in the 95 used ascii characters for text
	for (i = 0; i < 95; ++i)
	{
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);

		fin >> font[i].left;
		fin >> font[i].right;
		fin >> font[i].size;
	}

	// Close the file
	fin.close();

	return true;
}

void Font::ReleaseFontData()
{
	// Release the font data array
	if (font)
	{
		delete[] font;
		font = NULL;
	}

	return;
}

bool Font::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;

	// Create the texture object
	texture = new Texture;
	if (!texture)
	{
		return false;
	}

	// Initialise the texture object
	result = texture->Init(device, deviceContext, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

void Font::ReleaseTexture()
{
	// Release the texture object
	if (texture)
	{
		texture->CleanUp();
		delete texture;
		texture = NULL;
	}
}

ID3D11ShaderResourceView* Font::GetTexture()
{
	return texture->GetTexture();
}

void Font::BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, i, letter;

	// Coerce the input vertices into a VertexType structure
	vertexPtr = (VertexType*)vertices;

	// Get the number of letters in the sentence
	numLetters = (int)strlen(sentence);

	// Initialise the index to the vertex array
	index = 0;

	// Draw each letter on to a quad
	for (i = 0; i < numLetters; ++i)
	{
		letter = ((int)sentence[i]) - 32;

		// If the letter is a space then just move over three pixels
		if (letter == 0)
		{
			drawX = drawY + 3.0f;
		}
		else
		{
			// First triangle in quad.
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = XMFLOAT2(font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3((drawX + font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(font[letter].right, 1.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3(drawX, (drawY - 16), 0.0f);  // Bottom left.
			vertexPtr[index].texture = XMFLOAT2(font[letter].left, 1.0f);
			index++;

			// Second triangle in quad.
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = XMFLOAT2(font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3(drawX + font[letter].size, drawY, 0.0f);  // Top right.
			vertexPtr[index].texture = XMFLOAT2(font[letter].right, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3((drawX + font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(font[letter].right, 1.0f);
			index++;

			// Update the x location for drawing by the size of the letter and one pixel.
			drawX = drawX + font[letter].size + 1.0f;
		}
	}

	return;
}