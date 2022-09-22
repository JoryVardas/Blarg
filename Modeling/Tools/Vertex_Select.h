#include "Mesh.h"

#ifndef __VERTEX_SELECT_H__
#define __VERTEX_SELECT_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static Vertex* Vertex_Select(v5CArrayData<Vertex> vertexArray, float x, float y, float tollerance)
				{
					Array<int> indices;
					for (uint i = 0; i < vertexArray.GetLength(); i++){
						float vx = ConvertXWorldToScreen(vertexArray[i]->X);
						float vy = ConvertYWorldToScreen(vertexArray[i]->Y);
						if ((vx - tollerance < x) && (vx + tollerance > x) && (vy - tollerance < y) && (vy + tollerance > y)){
							indices.Add(i);
						};
					};
					if (indices.GetSize() == 0) return null;
					int ind = indices[0].GetData();
					float z = vertexArray[ind]->Z;
					for (int i = 1; i < indices.GetSize(); i++)
					{
						if (vertexArray[indices[i].GetData()]->Z < z)
						{
							ind = indices[i].GetData();
							z = vertexArray[ind]->Z;
						};
					};
					return vertexArray[ind];
				};
			};
		};
	};
};

#endif