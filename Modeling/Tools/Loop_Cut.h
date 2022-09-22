#include "3D-Modeling\Mesh.h"
#include "Edge_Data.h"
#include "Core\Array.h"
#include "3D-Modeling\Math.h"

#ifndef __LOOP_CUT_H__
#define __LOOP_CUT_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				struct Loop_Cut_Temp_Data
				{
					unsigned int originalIndex;
					unsigned int newIndex;
					bool mesh; //true is new mesh, false is old mesh.
					bool bottom;
				};

				static Mesh* Loop_Cut(Mesh* mesh, Vertex* selectedVerts)
				{
					BrokenTechStudios::Nuke::_3DModeling::Polygon p(&selectedVerts[0], &selectedVerts[1], &selectedVerts[2]);
					Array<Loop_Cut_Temp_Data> tempData;
					Array<Vertex> oldArray;
					Array<Vertex> newArray;
					for(int i = 0; i < mesh->GetNumberOfVertices; i++)
					{
						float abe = Dot(Vector(mesh->GetVertexArray()[i], selectedVerts[0]), p.GetNormal());
						if(abe == 0)
						{
							Loop_Cut_Temp_Data tdata = {i, oldArray.GetSize(), false, true};
							Loop_Cut_Temp_Data tdata2 = {i, newArray.GetSize(), true, true};
							oldArray.Add(mesh->GetVertexArray()[i]);
							newArray.Add(mesh->GetVertexArray()[i]);
							tempData.Add(tdata);
							tempData.Add(tdata2);
						}
						else if(abe > 0)
						{
							Loop_Cut_Temp_Data tdata = {i, newArray.GetSize(), true, false};
							newArray.Add(mesh->GetVertexArray()[i]);
							tempData.Add(tdata);
						}
						else if(abe < 0)
						{
							Loop_Cut_Temp_Data tdata = {i, newArray.GetSize(), false, false};
							oldArray.Add(mesh->GetVertexArray()[i]);
							tempData.Add(tdata);
						};
					};
					Array<WORD> oldIndex;
					Array<WORD> newIndex;
					for(int i = 0; i < mesh->GetNumberOfIndices(); i += 3)
					{
						int a = -1;
						int b = -1;
						int c = -1;
						for(int j = 0; j < tempData.GetSize(); j++)
						{
							if(tempData[j]->originalIndex == mesh->GetIndexArray()[i])
							{
								a = j;
							}
							else if(tempData[j]->originalIndex == mesh->GetIndexArray()[i + 1])
							{
								b = j;
							}
							else if(tempData[j]->originalIndex == mesh->GetIndexArray()[i + 2])
							{
								c = j;
							};
						};
						if(tempData[a]->mesh == tempData[b]->mesh == tempData[c]->mesh)
						{
							if(tempData[a]->mesh)
							{
								newIndex.Add(tempData[a]->newIndex);
								newIndex.Add(tempData[b]->newIndex);
								newIndex.Add(tempData[c]->newIndex);
							}
							else
							{
								oldIndex.Add(tempData[a]->newIndex);
								oldIndex.Add(tempData[b]->newIndex);
								oldIndex.Add(tempData[c]->newIndex);
							}
						};
					};
					mesh->SetVertexArray(v5CArrayData<Vertex>(oldArray.GetData(), oldArray.GetSize()));
					mesh->SetIndexArray(v5CArrayData<WORD>(oldIndex.GetData(), oldIndex.GetSize()));
					Mesh newMesh = *mesh;
					newMesh.SetVertexArray(v5CArrayData<Vertex>(newArray.GetData(), newArray.GetSize()));
					newMesh.SetIndexArray(v5CArrayData<WORD>(newIndex.GetData(), newIndex.GetSize()));
					return &newMesh;
				};
			};
		};
	};
};

#endif