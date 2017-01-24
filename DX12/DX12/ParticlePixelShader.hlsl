//--------------------------------------------------//
// Filename: ParticlePixelShader.hlsl				//
//--------------------------------------------------//

// Globals
Texture2D shaderTexture;
SamplerState sampleType;

// TypeDefs
struct PixelInput
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 colour : COLOUR;
};

float4 ParticlePixelShader(PixelInput input) : SV_TARGET
{
	float4 textureColour;
	float4 finalColour;

	// Sample the pixel colour from the texture using the sampler at this texture coordinate location
	textureColour = shaderTexture.Sample(sampleType, input.tex);

	// Combine the texture colour and the particle colour to get the final colour result
	finalColour = textureColour * input.colour;

	return finalColour;
}