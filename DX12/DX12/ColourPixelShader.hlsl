//--------------------------------------------------//
// Filename: ColourPixelShader.hlsl					//
//--------------------------------------------------//

// TypeDefs
struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 colour : COLOUR;
};

float4 ColourPixelShader(PixelInputType input) : SV_TARGET
{
	input.colour = float4(0.95f, 0.95f, 0.95f, 1.0f);
	return input.colour;
}