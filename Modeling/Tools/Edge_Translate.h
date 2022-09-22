#include "Vertex_Translate.h"
#include "Edge_Data.h"

#ifndef __EDGE_TRANSLATE_H__
#define __EDGE_TRANSLATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Edge_Translate(Edge_Data eData, float x, float y, float z)
				{
					Vertex_Translate(eData.GetVertex1(), x, y, z);
					Vertex_Translate(eData.GetVertex2(), x, y, z);
				};
			};
		};
	};
};

#endif