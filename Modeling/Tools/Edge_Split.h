#include "Face.h"
#include "Mesh.h"

#ifndef __EDGE_SPLIT_H__
#define __EDGE_SPLIT_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				//might not work
				static bool VertexComp(Vertex* v1, Vertex* v2)
				{
					return (v1->X == v2->X) && (v1->Y == v2->Y) && (v1->Z == v2->Z);
				};
				static void Edge_Split(Mesh* mesh, Vertex* v1, Vertex* v2)
				{
					uint e1Index = 0;
					uint e2Index = 0;
					for (int i = 0; i < mesh->GetNumberOfVertices(); i++)
					{
						if (VertexComp(mesh->GetVertex(i), v1)) e1Index = i;
						else if (VertexComp(mesh->GetVertex(i), v2)) e2Index = i;
					};

					//clears the color of the selected vertices so that the the selected data can be cleared without worry of invalid pointers.
					v1->Color = __WIREFRAME_VERTEX_DEFAULT_COLOR__;
					v2->Color = __WIREFRAME_VERTEX_DEFAULT_COLOR__;

					float vx = Average(v1->X, v2->X);
					float vy = Average(v1->Y, v2->Y);
					float vz = Average(v1->Z, v2->Z);

					Vertex v = { vx, vy, vz, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					uint vIndex = mesh->GetNumberOfVertices();
					mesh->AddVertex(v);
					//mesh->AddIndexTriangle(vIndex, e1Index, e2Index);

					for (int i = 0; i < mesh->GetNumberOfIndices(); i += 3)
					{
						uint ind = mesh->GetIndexArrayDirect().GetData()[i];
						uint ind1 = mesh->GetIndexArrayDirect().GetData()[i + 1];
						uint ind2 = mesh->GetIndexArrayDirect().GetData()[i + 2];

						bool indOnEdge = ind == e1Index || ind == e2Index;
						bool ind1OnEdge = ind1 == e1Index || ind1 == e2Index;
						bool ind2OnEdge = ind2 == e1Index || ind2 == e2Index;

						if (((int)indOnEdge + (int)ind1OnEdge + (int)ind2OnEdge) >= 2){

							if (!indOnEdge)
							{
								mesh->GetIndexArrayDirect().GetData()[i + 1] = vIndex;

								mesh->AddIndexTriangle(ind1, vIndex, ind);
							}
							else if (!ind1OnEdge)
							{
								mesh->GetIndexArrayDirect().GetData()[i] = vIndex;

								mesh->AddIndexTriangle(ind1, vIndex, ind);
							}
							else if (!ind2OnEdge)
							{
								mesh->GetIndexArrayDirect().GetData()[i] = vIndex;

								mesh->AddIndexTriangle(ind, vIndex, ind2);
							};
						};
					};
				};
			};
		};
	};
};

#endif