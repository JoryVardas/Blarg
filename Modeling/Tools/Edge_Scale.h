#include "Vertex_Scale.h"
#include "Edge_Data.h"

#ifndef __EDGE_SCALE_H__
#define __EDGE_SCALE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Edge_Scale(Edge_Data eData, float factor)
				{
					//float x = eData.GetVertex1()->X + ((eData.GetVertex1()->X - eData.GetVertex2()->X) / 2);
					//float y = eData.GetVertex1()->Y + ((eData.GetVertex1()->Y - eData.GetVertex2()->Y) / 2);
					//float z = eData.GetVertex1()->Z + ((eData.GetVertex1()->Z - eData.GetVertex2()->Z) / 2);
					Vector v(eData.GetVertex1(), eData.GetVertex2());
					Point3D p = v.GetPointAt(0.5);
					Vertex_Scale(eData.GetVertex1(), p, factor);
					Vertex_Scale(eData.GetVertex2(), p, factor);
				};
				
				static void Edge_Scale(Edge_Data eData, float factor, bool fromOrigin)
				{
					Vertex_Scale(eData.GetVertex1(), factor);
					Vertex_Scale(eData.GetVertex2(), factor);
				};

				static void Edge_Scale(Edge_Data eData, Point3D point, float factor)
				{
					Vertex_Scale(eData.GetVertex1(), point, factor);
					Vertex_Scale(eData.GetVertex2(), point, factor);
				};
			};
		};
	};
};
#endif