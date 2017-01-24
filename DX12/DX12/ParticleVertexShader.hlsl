//--------------------------------------------------//
// Filename: ParticleVertexShader.hlsl				//
//--------------------------------------------------//

// Globals
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

// TypeDefs
struct VertexInput
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float4 colour : COLOUR;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 colour : COLOUR;
};

PixelInput ParticleVertexShader(VertexInput input)
{
	PixelInput output;

	// Change the position vector to be 4 units for proper matrix calculations
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader
	output.tex = input.tex;

	// Store the particle colour for the pixel shader
	output.colour = input.colour;

	return output;
}