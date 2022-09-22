#include "Renderer.h"

#ifndef __SOLID_RENDERER_H__
#define __SOLID_RENDERER_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Rendering
		{
			using namespace BrokenTechStudios::Nuke::Core;

			class SolidRenderer : public Renderer
			{
			public:
				SolidRenderer(v5RenderState* renderState) : Renderer(renderState){
					InitializeRasterizerState();
					InitializeVertexShaderAndInputLayout();
					InitializePixelShader();
				};
				~SolidRenderer(){};

				void InitializeRasterizerState(){
					D3D11_RASTERIZER_DESC rdc;
					ZeroMemory(&rdc, sizeof(D3D11_RASTERIZER_DESC));
					rdc.FillMode = D3D11_FILL_SOLID;
					rdc.CullMode = D3D11_CULL_BACK;
					_RenderState->Device->CreateRasterizerState(&rdc, &_RasterizerState);
					_RenderState->DeviceContext->RSSetState(_RasterizerState);
				};
				void InitializeVertexShaderAndInputLayout(){
					ID3D10Blob* vertexShader;
					D3DX11CompileFromFile("..\\Rendering\\shaders.hlsl", 0, 0, "SolidRendererVertexShader", "vs_5_0", 0, 0, 0, &vertexShader, 0, 0);
					_RenderState->Device->CreateVertexShader(vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), null, &_VertexShader);
					_RenderState->Device->CreateInputLayout(VertexDescription, NumberOfVertexElements, vertexShader->GetBufferPointer(), vertexShader->GetBufferSize(), &_VertexInputLayout);
				};
				void InitializePixelShader(){
					ID3D10Blob* pixelShader;
					D3DX11CompileFromFile("..\\Rendering\\shaders.hlsl", 0, 0, "StandardPixelShader", "ps_5_0", 0, 0, 0, &pixelShader, 0, 0);
					_RenderState->Device->CreatePixelShader(pixelShader->GetBufferPointer(), pixelShader->GetBufferSize(), null, &_PixelShader);
				};
			};
		};
	};
};

#endif