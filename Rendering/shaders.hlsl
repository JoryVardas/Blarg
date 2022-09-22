struct StandardVertexOutputPixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

StandardVertexOutputPixelInput SolidRendererVertexShader(float4 pos : POSITION, float2 texCoords : TEXCOORD, float4 color : COLOR, float selected : SELECTED)
{
	StandardVertexOutputPixelInput output;
	output.position = pos;
	output.color = float4(1, 1, 1, 1);
	return output;
};

StandardVertexOutputPixelInput WireframeRendererVertexShader(float4 pos : POSITION, float2 texCoords : TEXCOORD, float4 color : COLOR, float selected : SELECTED)
{
	StandardVertexOutputPixelInput output;
	output.position = pos;
	output.color = color;
	return output;
};

StandardVertexOutputPixelInput VertexRendererVertexShader(float4 pos : POSITION, float2 texCoords : TEXCOORD, float4 color : COLOR, float selected : SELECTED)
{
	StandardVertexOutputPixelInput output;
	output.position = pos;
	output.color = float4(0, 1, 0, 1);
	return output;
};

float4 StandardPixelShader(StandardVertexOutputPixelInput input) : SV_TARGET
{
	return input.color;
};