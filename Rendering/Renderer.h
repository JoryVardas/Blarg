#include "Global_Variables.H"
#include "World.h"
#include "v5RenderState.h"

#ifndef __RENDERING_RENDERER_H__
#define __RENDERING_RENDERER_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Rendering
		{
			using namespace Core;
			using namespace _3DModeling;

			class Renderer
			{
			protected:
				ID3D11InputLayout* _VertexInputLayout;
				ID3D11RasterizerState* _RasterizerState;
				ID3D11VertexShader* _VertexShader;
				ID3D11PixelShader* _PixelShader;
				v5RenderState* _RenderState;
			public:
				Renderer()
				{
					_RenderState = null;
					_VertexShader = null;
					_PixelShader = null;
				};
				Renderer(v5RenderState* renderState){
					_RenderState = renderState;
					_VertexShader = null;
					_PixelShader = null;
				};
				~Renderer(){
					Release();
				};
				virtual void InitializeRasterizerState() = 0;
				virtual void InitializeVertexShaderAndInputLayout() = 0;
				virtual void InitializePixelShader() = 0;
				virtual void Draw(World* world){
					_RenderState->DeviceContext->IASetInputLayout(_VertexInputLayout);
					_RenderState->DeviceContext->RSSetState(_RasterizerState);
					_RenderState->DeviceContext->VSSetShader(_VertexShader, 0, 0);
					_RenderState->DeviceContext->PSSetShader(_PixelShader, 0, 0);
					for(int i = 0; i < world->GetNumberOfMeshs(); i++)
					{
						_RenderState->UpdateVertexBuffer(world->_Meshs[i]->GetVertexArrayDirect());
						_RenderState->UpdateIndexBuffer(world->_Meshs[i]->GetIndexArrayDirect());

						_RenderState->DeviceContext->IASetVertexBuffers(0, 1, &_RenderState->VertexBuffer, &VertexStride, &Offset);
						_RenderState->DeviceContext->IASetIndexBuffer(_RenderState->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
						_RenderState->DeviceContext->DrawIndexed(world->_Meshs[i]->GetNumberOfIndices(), 0, 0);
					};
				};
				virtual void Release(){
					if(_VertexInputLayout) _VertexInputLayout->Release();
					if(_RasterizerState) _RasterizerState->Release();
					if(_VertexShader) _VertexShader->Release();
					if(_PixelShader) _PixelShader->Release();
				};
			};
		};
	};
};

#endif