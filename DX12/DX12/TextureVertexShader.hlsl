//--------------------------------------------------//
// Filename: TextureVertexShader.hlsl				//
//--------------------------------------------------//

// Globals
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

/* RasterTek comment
We are no longer using color in our vertex type and have instead moved to using texture coordinates. Since texture coordinates take a U and V float coordinate we use 
float2 as its type. The semantic for texture coordinates is TEXCOORD0 for vertex shaders and pixel shaders. You can change the zero to any number to indicate which
set of coordinates you are working with as multiple texture coordinates are allowed.
*/

// TypeDefs
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 instancePosition : TEXCOORD1;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

PixelInputType TextureVertexShader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Update the position of the vertices based on the data for this particular instance.
	input.position.x += input.instancePosition.x;
	input.position.y += input.instancePosition.y;
	input.position.z += input.instancePosition.z;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	return output;
}