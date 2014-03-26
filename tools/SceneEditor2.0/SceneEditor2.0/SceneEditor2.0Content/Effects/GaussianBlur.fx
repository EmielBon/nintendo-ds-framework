sampler2D input : register(s0);

float kernel[9] = { 0.0162162162, 0.0540540541, 0.1216216216, 0.1945945946, 0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162 };
//float kernel[9] = { 1/9.0f, 1/9.0f, 1/9.0f, 1/9.0f, 1/9.0f, 1/9.0f, 1/9.0f, 1/9.0f, 1/9.0f };

float4 HorizontalBlurPS(float2 uv : TEXCOORD) : COLOR0 
{ 
    float4 color = {0, 0, 0, 1};
	
	for(int i = -4; i < 4; ++i)
	{
		color += tex2D(input, float2(uv.x + i / 1024.0f, uv.y)) * kernel[i + 4];
	}

	return color;
}

float4 VerticalBlurPS(float2 uv : TEXCOORD) : COLOR0 
{ 
    float4 color = {0, 0, 0, 1};
	
	for(int i = -4; i < 4; ++i)
	{
		color += tex2D(input, float2(uv.x, uv.y + i / 768.0f)) * kernel[i + 4];
	}

	return color;
}

technique Blur
{
	pass Pass1
	{
		PixelShader = compile ps_2_0 HorizontalBlurPS();
	}
	pass Pass2
	{
		PixelShader = compile ps_2_0 VerticalBlurPS();
	}
}