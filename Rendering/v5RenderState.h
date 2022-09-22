#include "Global_Variables.h"
#include "Window.h"
#include "v5CArrayData.h"
#include "Vertex.h"

#ifndef __V5_RENDER_STATE_H__
#define __V5_RENDER_STATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Rendering
		{
			using namespace BrokenTechStudios::Nuke::Core;
			using namespace BrokenTechStudios::Nuke::UI;
			using namespace BrokenTechStudios::Nuke::_3DModeling;

			struct v5RenderState
			{
				IDXGISwapChain* SwapChain;
				ID3D11Device* Device;
				ID3D11DeviceContext* DeviceContext;
				ID3D11RenderTargetView* BackBuffer;
				//ID3D11InputLayout* VertexInputLayout;//moved to render engine, as it is dependent of the vertex shader being used.
				//ID3D11RasterizerState* RasterizerState;//moved to render engine, as it is dependent on the type of rendering being done.
				ID3D11Texture2D* DepthStencilTexture;
				ID3D11DepthStencilView* DepthStencilView;
				ID3D11DepthStencilState* DepthStencilState;
				Window* RenderWindow;
				ID3D11Buffer* VertexBuffer;
				ID3D11Buffer* IndexBuffer;

				v5RenderState(){
					VertexBuffer = IndexBuffer = null;
				};
				v5RenderState(Window* window){
					RenderWindow = window;
					InitializeDeviceAndSwapChain();
					InitializeBackBuffer();
					InitializeViewport();
					InitializeDepthBuffer();
					DeviceContext->OMSetDepthStencilState(DepthStencilState, 1);
					DeviceContext->OMSetRenderTargets(1, &BackBuffer, DepthStencilView);
					DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
					VertexBuffer = IndexBuffer = null;
				};
				~v5RenderState(){
					Release();
				};

				void InitializeDeviceAndSwapChain(){
					DXGI_SWAP_CHAIN_DESC swapChainDesc;
					ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
					swapChainDesc.BufferCount = 1;
					swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
					swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					swapChainDesc.BufferDesc.Width = RenderWindow->GetWidth();
					swapChainDesc.BufferDesc.Height = RenderWindow->GetHeight();
					swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
					swapChainDesc.OutputWindow = RenderWindow->GetHandle();
					swapChainDesc.SampleDesc.Count = 1;
					swapChainDesc.SampleDesc.Quality = 0;
					swapChainDesc.Windowed = true;
					swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

					D3D11CreateDeviceAndSwapChain(null, D3D_DRIVER_TYPE_HARDWARE, null, null, null, null, D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &Device, null, &DeviceContext);
				};
				void InitializeBackBuffer(){
					ID3D11Texture2D* backBufferTexture;
					SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
					Device->CreateRenderTargetView(backBufferTexture, null, &BackBuffer);
					backBufferTexture->Release();
				};
				void InitializeViewport(){
					D3D11_VIEWPORT viewport;
					ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
					viewport.TopLeftX = 0;
					viewport.TopLeftY = 0;
					viewport.MinDepth = 0.0f;
					viewport.MaxDepth = 1.0f;
					viewport.Width = RenderWindow->GetWidth();
					viewport.Height = RenderWindow->GetHeight();
					DeviceContext->RSSetViewports(1, &viewport);
				};
				void InitializeDepthBuffer(){
					D3D11_DEPTH_STENCIL_DESC dsDesc;
					// Depth test parameters
					dsDesc.DepthEnable = true;
					dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
					dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

					// Stencil test parameters
					dsDesc.StencilEnable = true;
					dsDesc.StencilReadMask = 0xFF;
					dsDesc.StencilWriteMask = 0xFF;

					// Stencil operations if pixel is front-facing
					dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
					dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;

					// Stencil operations if pixel is back-facing
					dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
					dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;
					Device->CreateDepthStencilState(&dsDesc, &DepthStencilState);

					D3D11_TEXTURE2D_DESC depthTexDesc;
					ZeroMemory(&depthTexDesc, sizeof(D3D11_TEXTURE2D_DESC));
					depthTexDesc.Width = RenderWindow->GetWidth();
					depthTexDesc.Height = RenderWindow->GetHeight();
					depthTexDesc.MipLevels = 1;
					depthTexDesc.ArraySize = 1;
					depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
					depthTexDesc.SampleDesc.Count = 1;
					depthTexDesc.SampleDesc.Quality = 0;
					depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
					depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
					depthTexDesc.CPUAccessFlags = 0;
					depthTexDesc.MiscFlags = 0;

					Device->CreateTexture2D(&depthTexDesc, NULL, &DepthStencilTexture);

					D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
					ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
					descDSV.Format = depthTexDesc.Format;
					descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
					descDSV.Texture2D.MipSlice = 0;

					Device->CreateDepthStencilView(DepthStencilTexture, &descDSV, &DepthStencilView);
				};
				void Present(){
					SwapChain->Present(0, 0);
				};
				void UpdateVertexBuffer(v5CArrayData<Vertex> vertices){
					if(VertexBuffer) VertexBuffer->Release();
					if(vertices.GetLength() > 0){
					D3D11_BUFFER_DESC bufferDesc;
					ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
					bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
					bufferDesc.ByteWidth = VertexStride * vertices.GetLength();
					bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					Device->CreateBuffer(&bufferDesc, null, &VertexBuffer);
					D3D11_MAPPED_SUBRESOURCE mappedSubresource;
					DeviceContext->Map(VertexBuffer, null, D3D11_MAP_WRITE_DISCARD, null, &mappedSubresource);
					memcpy(mappedSubresource.pData, vertices.GetData(), VertexStride * vertices.GetLength());
					DeviceContext->Unmap(VertexBuffer, null);
					};
				};
				void UpdateIndexBuffer(v5CArrayData<WORD> indices){
					if(IndexBuffer) IndexBuffer->Release();
					if(indices.GetLength() > 0){
					D3D11_BUFFER_DESC bufferDesc;
					ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
					bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
					bufferDesc.ByteWidth = sizeof(WORD) * indices.GetLength();
					bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
					bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

					Device->CreateBuffer(&bufferDesc, NULL, &IndexBuffer);

					D3D11_MAPPED_SUBRESOURCE mappedSubresource;
					DeviceContext->Map(IndexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource);
					memcpy(mappedSubresource.pData, indices.GetData(), sizeof(WORD) * indices.GetLength());
					DeviceContext->Unmap(IndexBuffer, NULL);
					};
				};
				void Release(){
					if(SwapChain) SwapChain->Release();
					if(Device) Device->Release();
					if(DeviceContext) DeviceContext->Release();
					if(BackBuffer) BackBuffer->Release();
					if(DepthStencilTexture) DepthStencilTexture->Release();
					if(DepthStencilView) DepthStencilView->Release();
					if(DepthStencilState) DepthStencilState->Release();
				};
				void ClearDisplay()
				{
					DeviceContext->ClearRenderTargetView(BackBuffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
					DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
				};
			};
		};
	};
};
#endif