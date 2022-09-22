#include "3D-Modeling\Vertex.h"

#ifndef __AVERAGE_VERTEX_POSITION__
#define __AVERAGE_VERTEX_POSITION__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Average_Vertex_Position(Vertex* a, Vertex* b)
				{
					float x = (a->X + b->X) / 2;
					float y = (a->Y + b->Y) / 2;
					float z = (a->Z + b->Z) / 2;

					a->X = x;
					a->Y = y;
					a->Z = z;
					b->X = x;
					b->Y = y;
					b->Z = z;
				};
			};
		};
	};
};

#endif