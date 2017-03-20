//--------------------------------------------------//
// Filename: ColourVertexShader.hlsl				//
//--------------------------------------------------//

// Globals
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

// TypeDefs
struct VertexInputType
{
	float4 position : POSITION;
	//float3 normal : NORMAL;
	float4 colour : COLOUR;
	float3 instancePosition : TEXCOORD1;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 colour : COLOUR;
	//float3 normal : NORMAL;
};

PixelInputType ColourVertexShader(VertexInputType input)
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

	// Store the input color for the pixel shader to use.
	output.colour = input.colour;

	// Normalize the normal vector.
	//output.normal = normalize(output.normal);

	return output;
}