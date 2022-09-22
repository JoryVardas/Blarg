#include "Mesh.h"
#include "Vertex_Scale.h"

#ifndef __FACE_SCALE_H__
#define __FACE_SCALE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Face_Scale(Face face, float factor)
				{
					Vertex_Scale(face.GetVertex1(), face.GetCenterPoint(), factor);
					Vertex_Scale(face.GetVertex2(), face.GetCenterPoint(), factor);
					Vertex_Scale(face.GetVertex3(), face.GetCenterPoint(), factor);
					Vertex_Scale(face.GetVertex4(), face.GetCenterPoint(), factor);
				};
				static void Face_Scale(Face face, Point3D centerOfScale, float factor)
				{
					Vertex_Scale(face.GetVertex1(), centerOfScale, factor);
					Vertex_Scale(face.GetVertex2(), centerOfScale, factor);
					Vertex_Scale(face.GetVertex3(), centerOfScale, factor);
					Vertex_Scale(face.GetVertex4(), centerOfScale, factor);
				};
				static void Face_Scale(Face face, float x, float y, float z)
				{
					Vertex_Scale(face.GetVertex1(), face.GetCenterPoint(), x, y, z);
					Vertex_Scale(face.GetVertex2(), face.GetCenterPoint(), x, y, z);
					Vertex_Scale(face.GetVertex3(), face.GetCenterPoint(), x, y, z);
					Vertex_Scale(face.GetVertex4(), face.GetCenterPoint(), x, y, z);
				};
				static void Face_Scale(Face face, Point3D centerOfScale, float x, float y, float z)
				{
					Vertex_Scale(face.GetVertex1(), centerOfScale, x, y, z);
					Vertex_Scale(face.GetVertex2(), centerOfScale, x, y, z);
					Vertex_Scale(face.GetVertex3(), centerOfScale, x, y, z);
					Vertex_Scale(face.GetVertex4(), centerOfScale, x, y, z);
				};
			};
		};
	};
};
#endif