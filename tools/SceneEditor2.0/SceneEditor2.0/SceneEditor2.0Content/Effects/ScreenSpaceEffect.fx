float ScreenWidth;
float ScreenHeight;
float4x4 World;

struct VertexShaderInput
{
    float4 Position : POSITION0;
	float4 Color    : COLOR0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
	float4 Color    : COLOR0;
};

VertexShaderOutput VertexShaderFunction(VertexShaderInput input)
{
    VertexShaderOutput output = (VertexShaderOutput)0;
	
	input.Position = mul(input.Position, World);

    output.Position.x = lerp(-1, 1, input.Position.x / ScreenWidth);
	output.Position.y = -lerp(-1, 1, input.Position.y / ScreenHeight);
	output.Position.z = 0;
	output.Position.w = 1;
	output.Color      = input.Color;

    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    return input.Color;
}

technique Technique1
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}
