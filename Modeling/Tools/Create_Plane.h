#include "Mesh.h"
#include "Vertex.h"

#ifndef __CREATE_PLANE_H__
#define __CREATE_PLANE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				using namespace BrokenTechStudios::Nuke::Core;
				using namespace BrokenTechStudios::Nuke::_3DModeling;
				
				static void Create_Plane(Mesh* mesh, Point3D origin, uint verticalCuts, uint horizontalCuts, float width)
				{
					Array<Vertex> vertices;
					verticalCuts;
					horizontalCuts;
					for(uint a = 0; a < horizontalCuts; a++)
					{
						float x = (a * (width / horizontalCuts)) + origin.GetX();
						for(uint b = 0; b < verticalCuts; b++)
						{
							float z = (b * (width / verticalCuts)) + origin.GetZ();
							Vertex v = {x, origin.GetY(), z, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
							vertices.Add(v);
						};
					};
					mesh->SetVertexArray(vertices.GetDataActual());
					for(uint a = 0; a < horizontalCuts - 1; a++)
					{
						for(uint b = 0; b < verticalCuts - 1; b++)
						{
							WORD index = (a * verticalCuts) + b;
							WORD index2 = (a * verticalCuts) + b + 1;
							WORD index3 = ((a+1) * verticalCuts) + b;
							WORD index4 = ((a+1) * verticalCuts) + b + 1;
							mesh->AddIndexQuad(index, index2, index3, index4);
						};
					};
					mesh->SetUsesTriangleFaces(true);
				};
				static void Create_Plane(Mesh* mesh, uint verticalCuts, uint horizontalCuts, float width, bool centered)
				{
					Point3D origin(-(width/2), 0, -(width/2));
					Array<Vertex> vertices;
					verticalCuts;
					horizontalCuts;
					for(uint a = 0; a < horizontalCuts; a++)
					{
						float x = (a * (width / horizontalCuts)) + origin.GetX();
						for(uint b = 0; b < verticalCuts; b++)
						{
							float z = (b * (width / verticalCuts)) + origin.GetZ();
							Vertex v = {x, origin.GetY(), z, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
							vertices.Add(v);
						};
					};
					mesh->SetVertexArray(vertices.GetDataActual());
					for(uint a = 0; a < horizontalCuts - 1; a++)
					{
						for(uint b = 0; b < verticalCuts - 1; b++)
						{
							WORD index = (a * verticalCuts) + b;
							WORD index2 = (a * verticalCuts) + b + 1;
							WORD index3 = ((a+1) * verticalCuts) + b;
							WORD index4 = ((a+1) * verticalCuts) + b + 1;
							mesh->AddIndexQuad(index, index2, index3, index4);
						};
					};
					mesh->SetUsesTriangleFaces(true);
				};
				static void Create_Plane(Mesh* mesh, uint verticalCuts, uint horizontalCuts, float width, bool centered, Point3D center)
				{
					Point3D origin(-(width/2) + center.GetX(), 0, -(width/2) + center.GetZ());
					Array<Vertex> vertices;
					verticalCuts;
					horizontalCuts;
					for(uint a = 0; a < horizontalCuts; a++)
					{
						float x = (a * (width / horizontalCuts)) + origin.GetX();
						for(uint b = 0; b < verticalCuts; b++)
						{
							float z = (b * (width / verticalCuts)) + origin.GetZ();
							Vertex v = {x, center.GetY(), z, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
							vertices.Add(v);
						};
					};
					mesh->SetVertexArray(vertices.GetDataActual());
					for(uint a = 0; a < horizontalCuts - 1; a++)
					{
						for(uint b = 0; b < verticalCuts - 1; b++)
						{
							WORD index = (a * verticalCuts) + b;
							WORD index2 = (a * verticalCuts) + b + 1;
							WORD index3 = ((a+1) * verticalCuts) + b;
							WORD index4 = ((a+1) * verticalCuts) + b + 1;
							mesh->AddIndexQuad(index, index2, index3, index4);
						};
					};
					mesh->SetUsesTriangleFaces(true);
				};
			};
		};
	};
};

#endif