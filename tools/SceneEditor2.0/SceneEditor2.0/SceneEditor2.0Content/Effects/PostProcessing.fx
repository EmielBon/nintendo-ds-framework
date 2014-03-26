//------------------------------------- Top Level Variables -------------------------------------

sampler2D input : register(S0);

//------------------------------------ Technique: Monochrome ------------------------------------

float4 MonochromePS(float2 uv : TEXCOORD) : COLOR0
{
	float4 color             = tex2D(input, uv);
	float3 monochromeWeights = {0.2126, 0.7152, 0.0722};
	float  y                 = dot((float3)color, monochromeWeights);
	
	return float4(y, y, y, 1);
}

technique Monochrome
{
	pass Pass1
	{
		PixelShader = compile ps_2_0 MonochromePS();
	}
}

//-------------------------------- Technique: NoPostProcessing ----------------------------------

float4 NoPostProcessingPS(float2 uv : TEXCOORD) : COLOR0
{
	return tex2D(input, uv);
}

technique NoPostProcessing
{
	pass Pass0
	{
		PixelShader  = compile ps_2_0 NoPostProcessingPS();
	}
}