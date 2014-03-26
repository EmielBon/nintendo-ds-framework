sampler2D input : register(s0);

texture AlternativeTexture;
sampler AlternativeSampler = sampler_state 
{
	Texture = <AlternativeTexture>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

texture MaskTexture;
sampler MaskSampler = sampler_state 
{ 
	Texture = <MaskTexture>;
    MinFilter = Point;
    MagFilter = Point;
    MipFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};

float4 PixelShaderFunction(float2 uv : TEXCOORD) : COLOR0
{
    float pixelMask = tex2D(MaskSampler, uv).r;

    return lerp(tex2D(input, uv), tex2D(AlternativeSampler, uv), pixelMask);
}

technique Mask
{
    pass Pass1
    {
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}
