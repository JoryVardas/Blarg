#include "3D-Modeling\Mesh.h"

#ifndef __FRACTALIZE_H__
#define __FRACTALIZE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Fractalize(Mesh* mesh, BrokenTechStudios::Nuke::_3DModeling::Polygon poly)
				{
					float v1v2HalfX = (poly.GetVertex1()->X + poly.GetVertex2()->X) / 2;
					float v1v3HalfX = (poly.GetVertex1()->X + poly.GetVertex3()->X) / 2;
					float v2v3HalfX = (poly.GetVertex2()->X + poly.GetVertex3()->X) / 2;
					float v1v2HalfY = (poly.GetVertex1()->Y + poly.GetVertex2()->Y) / 2;
					float v1v3HalfY = (poly.GetVertex1()->Y + poly.GetVertex3()->Y) / 2;
					float v2v3HalfY = (poly.GetVertex2()->Y + poly.GetVertex3()->Y) / 2;
					float v1v2HalfZ = (poly.GetVertex1()->Z + poly.GetVertex2()->Z) / 2;
					float v1v3HalfZ = (poly.GetVertex1()->Z + poly.GetVertex3()->Z) / 2;
					float v2v3HalfZ = (poly.GetVertex2()->Z + poly.GetVertex3()->Z) / 2;
					
					Vertex v1 = *poly.GetVertex1();
					Vertex v2 = *poly.GetVertex2();
					Vertex v3 = *poly.GetVertex3();
					Vertex v12 = v1;
					Vertex v13 = v1;
					Vertex v23 = v1;
					v12.X = v1v2HalfX;
					v12.Y = v1v2HalfY;
					v12.Z = v1v2HalfZ;
					v13.X = v1v3HalfX;
					v13.Y = v1v3HalfY;
					v13.Z = v1v3HalfZ;
					v23.X = v2v3HalfX;
					v23.Y = v2v3HalfY;
					v23.Z = v2v3HalfZ;

					*(poly.GetVertex1()) = v1;
					*(poly.GetVertex2()) = v12;
					*(poly.GetVertex3()) = v13;
					mesh->AddVertexTriangle(&v13, &v12, &v23);
					mesh->AddVertexTriangle(&v12, &v2, &v23);
					mesh->AddVertexTriangle(&v3, &v23, &v13);
				};
			};
		};
	};
};

#endif