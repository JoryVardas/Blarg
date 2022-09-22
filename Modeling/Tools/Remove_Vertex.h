#include "3D-Modeling\Mesh.h"

#ifndef __REMOVE_VERTEX_H__
#define __REMOVE_VERTEX_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				using namespace BrokenTechStudios::Nuke::Core;

				static void Remove_Vertex(Mesh* mesh, Vertex* vert)
				{
					Array<WORD> temp;
					unsigned int index = (unsigned int)vert - (unsigned int)mesh->GetVertexArray();
					for(int i = 0; i < mesh->GetNumberOfIndices; i += 3)
					{
						if(!((mesh->GetIndexArray()[i] == index) || (mesh->GetIndexArray()[i + 1] == index) || (mesh->GetIndexArray()[i + 2] == index)))
						{
							temp.Add(mesh->GetIndexArray()[i]);
							temp.Add(mesh->GetIndexArray()[i + 1]);
							temp.Add(mesh->GetIndexArray()[i + 2]);
						};
					};
					mesh->SetIndexArray(v5CArrayData<WORD>(temp.GetData(), temp.GetSize()));
				};
			};
		};
	};
};

#endif