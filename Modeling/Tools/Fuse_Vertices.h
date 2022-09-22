#include "Mesh.h"

#ifndef __FUSE_VERTICES_H__
#define __FUSE_VERTICES_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				using namespace BrokenTechStudios::Nuke::Core;

				static bool Fuse_Vertices_VertexComp(Vertex* v1, Vertex* v2)
				{
					return (v1->X == v2->X) && (v1->Y == v2->Y) && (v1->Z == v2->Z);
				};
				static void Fuse_Vertices(Mesh* mesh, Vertex* v1, Vertex* v2)
				{
					uint e1Index = 0;
					uint e2Index = 0;
					for (int i = 0; i < mesh->GetNumberOfVertices(); i++)
					{
						if (Fuse_Vertices_VertexComp(mesh->GetVertex(i), v1)) e1Index = i;
						else if (Fuse_Vertices_VertexComp(mesh->GetVertex(i), v2)) e2Index = i;
					};

					//clears the color of the selected vertices so that the the selected data can be cleared without worry of invalid pointers.
					v1->Color = __WIREFRAME_VERTEX_DEFAULT_COLOR__;
					v2->Color = __WIREFRAME_VERTEX_DEFAULT_COLOR__;

					float vx = Average(v1->X, v2->X);
					float vy = Average(v1->Y, v2->Y);
					float vz = Average(v1->Z, v2->Z);

					Vertex v = { vx, vy, vz, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					mesh->GetVertexArrayDirect().GetData()[e1Index] = v;

					for (int i = 0; i < mesh->GetNumberOfIndices(); i++)
					{
						if (mesh->GetIndexArrayDirect().GetData()[i] == e2Index)
						{
							mesh->GetIndexArrayDirect().GetData()[i] = e1Index;
						};
					};
					
					Vertex unUsed = { 0, 0, 0, 0, 0, D3DXCOLOR(0, 0, 0, 0), -1 };
					mesh->GetVertexArrayDirect().GetData()[e2Index] = unUsed;
				};
			};
		};
	};
};

#endif