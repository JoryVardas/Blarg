#include "World.h"
#include "Conversions.h"

#ifndef __VERTEX_SQUARE_CREATOR_H__
#define __VERTEX_SQUARE_CREATOR_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				using namespace BrokenTechStudios::Nuke::Core;

				static void VertexSquareCreator(World* world, Mesh* meshOut, float screenWidth, float screenHeight)
				{
					float width = ConvertScreenCoordsToWorldCoords(Coordinates(5, 5), screenWidth, screenHeight).X;
					for(uint a = 0; a < world->GetNumberOfMeshs(); a++)
					{
						v5CArrayData<Vertex> verts = world->_Meshs[a].GetData()->GetVertexArrayPtr();
						for(uint b = 0; b < verts.GetLength(); b++)
						{
							Vertex v = *verts[b];
							if(v.Selected == 1)
							{
								Vertex v1 = {v.X - width, v.Y + width, 0, 0, 0, D3DXCOLOR(1, 0, 0, 1)};
								Vertex v2 = {v.X + width, v.Y + width, 0, 0, 0, D3DXCOLOR(1, 0, 0, 1)};
								Vertex v3 = {v.X - width, v.Y - width, 0, 0, 0, D3DXCOLOR(1, 0, 0, 1)};
								Vertex v4 = {v.X + width, v.Y - width, 0, 0, 0, D3DXCOLOR(1, 0, 0, 1)};
								meshOut->AddVertexQuad(v1, v2, v3, v4);
							}
							else
							{
								Vertex v1 = {v.X - width, v.Y + width, 0, 0, 0, D3DXCOLOR(0, 0, 0, 1)};
								Vertex v2 = {v.X + width, v.Y + width, 0, 0, 0, D3DXCOLOR(0, 0, 0, 1)};
								Vertex v3 = {v.X - width, v.Y - width, 0, 0, 0, D3DXCOLOR(0, 0, 0, 1)};
								Vertex v4 = {v.X + width, v.Y - width, 0, 0, 0, D3DXCOLOR(0, 0, 0, 1)};
								meshOut->AddVertexQuad(v1, v2, v3, v4);
							};
						};
					};
				};
			};
		};
	};
};

#endif