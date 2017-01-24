//--------------------------------------------------//
// Filename: TexturePixelShader.hlsl				//
//--------------------------------------------------//

// Globals
Texture2D shaderTexture;
SamplerState sampleType;

// TypeDefs
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 TexturePixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(sampleType, input.tex);

	return textureColor;
}