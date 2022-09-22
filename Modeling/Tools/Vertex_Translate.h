#include "Vertex.h"

#ifndef __VERTEX_TRANSLATE_H__
#define __VERTEX_TRANSLATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Vertex_Translate(Vertex* vert, float x, float y, float z)
				{
					if(vert != null)
					{
						vert->X += x;
						vert->Y += y;
						vert->Z += z;
					};
				};
			};
		};
	};
};

#endif