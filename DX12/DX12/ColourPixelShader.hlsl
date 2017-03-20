//--------------------------------------------------//
// Filename: ColourPixelShader.hlsl					//
//--------------------------------------------------//

// TypeDefs
struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 colour : COLOUR;
	//float3 normal : NORMAL;
};

float4 ColourPixelShader(PixelInputType input) : SV_TARGET
{
	return input.colour;
}