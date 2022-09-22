#include "3D-Modeling\Mesh.h"

#ifndef __REMOVE_DUPLICATES_H__
#define __REMOVE_DUPLICATES_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				using namespace BrokenTechStudios::Nuke::Core;

				struct Remove_Duplicate_Position_Data
				{
					int initialPos;
					int finalPos;

					Remove_Duplicate_Position_Data(float a, float b)
					{
						initialPos = a;
						finalPos = b;
					};
				};

				static bool Vertex_Position_Equals(Vertex* v1, Vertex* v2, float tollerance)
				{
					return ((((v1->X - tollerance) < v2->X) && ((v1->X + tollerance) > v2->X)) && (((v1->Y - tollerance) < v2->Y) && ((v1->Y + tollerance) > v2->Y)) && (((v1->Z - tollerance) < v2->Z) && ((v1->Z + tollerance) > v2->Z)));
				};

				static void Remove_Duplicates(Mesh* mesh, float tollerance)
				{
					Array<Vertex> verts;
					Array<Remove_Duplicate_Position_Data> locations;

					for(int i = 0; i < mesh->GetNumberOfVertices(); i++)
					{
						bool alreadyExists = false;
						int position = 0;
						for(int j = 0; j < verts.GetSize(); j++)
						{
							if(Vertex_Position_Equals(&mesh->GetVertexArray[i], &verts[j].GetData(), tollerance))
							{
								alreadyExists = true;
								position = j;
								break;
							};
						};
						if(alreadyExists)
						{
							locations.Add(Remove_Duplicate_Position_Data(i, position));
						}
						else
						{
							locations.Add(Remove_Duplicate_Position_Data(i, verts.GetSize()));
							verts.Add(mesh->GetVertexArray()[i]);
						};
					};
					for(int i = 0; i < locations.GetSize(); i++)
					{
						Replace_Every_Instance_Of(mesh->GetIndexArray(), mesh->GetNumberOfIndices(), locations[i]->initialPos, locations[i]->finalPos);
					};
					mesh->SetVertexArray(v5CArrayData<Vertex>(verts.GetData(), verts.GetSize()));
				};
			};
		};
	};
};

#endif