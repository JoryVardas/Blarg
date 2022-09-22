#include "Mesh.h"
#include "Edge_Data.h"
#include "Add_Vertex.h"

#ifndef __EDGE_SELECT_H__
#define __EDGE_SELECT_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{

				static bool Edge_Click_Intersection_Check(Edge_Data ed, float x, float y, float tollerance)
				{
					float rise = (ed.GetVertex2()->Y - ed.GetVertex1()->Y);
					float run = (ed.GetVertex2()->X - ed.GetVertex1()->X);
					if((rise == 0) && ed.GetVertex1()->X == x) return true;
					else if((run == 0) && ed.GetVertex1()->Y == y) return true;
					else
					{
						float m = rise / run;
						float Py = (m * (x - ed.GetVertex1()->X)) + ed.GetVertex1()->X;
						float distance = sqrt((y - Py) * (y - Py));
						return distance <= tollerance;
					};
				};

				static Edge_Data Edge_Select(Mesh* mesh, float x, float y, float tollerance)
				{
					//Array<Temp_Edge_Data> tempEdges;
					for(uint i = 0; i < mesh->GetNumberOfFaces(); i++)
					{
						Face face = mesh->GetNthFace(i);
						Vertex* v1 = face.GetVertex1();
						Vertex* v2 = face.GetVertex2();
						Vertex* v3 = face.GetVertex3();
						Vertex* v4 = face.GetVertex4();
						
						Edge_Data e1(v1, v2, mesh);
						Edge_Data e2(v2, v2, mesh);
						Edge_Data e3(v3, v4, mesh);
						Edge_Data e4(v4, v1, mesh);
						
						if(Edge_Click_Intersection_Check(e1, x, y, tollerance))return e1;
						else if(Edge_Click_Intersection_Check(e2, x, y, tollerance))return e2;
						else if(Edge_Click_Intersection_Check(e3, x, y, tollerance))return e3;
						else if(Edge_Click_Intersection_Check(e4, x, y, tollerance))return e4;
					};
					return Edge_Data(null, null, null);
				};
			};
		};
	};
};
#endif