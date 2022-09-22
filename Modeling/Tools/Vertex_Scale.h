#include "Vertex.h"
#include "Ray.h"
#include "Point.h"

#ifndef __VERTEX_SCALE_H__
#define __VERTEX_SCALE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Vertex_Scale(Vertex* vert, float factor)
				{
					vert->X *= factor;
					vert->Y *= factor;
					vert->Z *= factor;
				};

				static void Vertex_Scale(Vertex* vert, float x, float y, float z)
				{
					vert->X *= x;
					vert->Y *= y;
					vert->Z *= z;
				};

				static void Vertex_Scale(Vertex* vert, Point3D centerOfScale, float factor)
				{
					vert->X -= centerOfScale.GetX();
					vert->Y -= centerOfScale.GetY();
					vert->Z -= centerOfScale.GetZ();
					vert->X *= factor;
					vert->Y *= factor;
					vert->Z *= factor;
					vert->X += centerOfScale.GetX();
					vert->Y += centerOfScale.GetY();
					vert->Z += centerOfScale.GetZ();
				};

				static void Vertex_Scale(Vertex* vert, Point3D centerOfScale, float x, float y, float z)
				{
					vert->X -= centerOfScale.GetX();
					vert->Y -= centerOfScale.GetY();
					vert->Z -= centerOfScale.GetZ();
					vert->X *= x;
					vert->Y *= y;
					vert->Z *= z;
					vert->X += centerOfScale.GetX();
					vert->Y += centerOfScale.GetY();
					vert->Z += centerOfScale.GetZ();
				};
			};
		};
	};
};

#endif