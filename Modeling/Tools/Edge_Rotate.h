#include "Point.h"
#include "Edge_Data.h"
#include "Vertex_Rotate.h"

#ifndef __EDGE_ROTATE_H__
#define __EDGE_ROTATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Edge_Rotate(Edge_Data eData, Point3D rotationCenter, float x, float y, float z)
				{
					Vertex_Rotate(eData.GetVertex1(), rotationCenter, x, y, z);
					Vertex_Rotate(eData.GetVertex2(), rotationCenter, x, y, z);
				};

				static void Edge_Rotate(Edge_Data eData, float x, float y, float z)
				{
					Vertex_Rotate(eData.GetVertex1(), Point3D(0, 0, 0), x, y, z);
					Vertex_Rotate(eData.GetVertex2(), Point3D(0, 0, 0), x, y, z);
				};
			};
		};
	};
};

#endif