//DONE

#include "Global_Variables.h"

#ifndef __VERTEX_H__
#define __VERTEX_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{

			//using namespace BrokenTechStudios::Nuke::Core;

			struct Vertex
			{
				FLOAT X, Y, Z;							//Position
				//FLOAT Highlighed;
				FLOAT U, V;							//Texture Coordinates
				D3DXCOLOR Color;						//The color of the vertex (used for highlighting the vertex when it is selected.
				FLOAT Selected;
				//FLOAT flags;							//Flags (use bit operators?)
				//FLOAT flag1, flag2, flag3, flag4;	//The Flag Info.
				//FLOAT flag5, flag6, flag7, flag8;
			};

			static D3D11_INPUT_ELEMENT_DESC VertexDescription[] = 
			{
					{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"SELECTED", 0, DXGI_FORMAT_R32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}
					//{"FLAGS", 0, DXGI_FORMAT_R32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
					//{"FLAGINFO1", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
					//{"FLAGINFO2", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

			static int NumberOfVertexElements = 4;
			static UINT VertexStride = sizeof(Vertex);
			static UINT Offset = 0;
		};
	};
};
#endif