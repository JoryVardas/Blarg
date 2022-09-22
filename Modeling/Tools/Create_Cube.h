#include "Global_Variables.h"
#include "Mesh.h"

#ifndef __CREATE_CUBE_H__
#define __CREATE_CUBE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				void Create_Cube(Mesh* mesh, float scale)
				{
					mesh->Clear();
					Vertex v1 = { -scale, scale, -scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v2 = { -scale, -scale, -scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v3 = { scale, scale, -scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v4 = { scale, -scale, -scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v5 = { -scale, scale, scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v6 = { -scale, -scale, scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v7 = { scale, scale, scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v8 = { scale, -scale, scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					mesh->AddVertexQuad(v1, v2, v3, v4);
					mesh->AddVertex(v5);
					mesh->AddVertex(v6);
					mesh->AddVertex(v7);
					mesh->AddVertex(v8);
					mesh->AddIndexQuad(7, 5, 6, 4);
					mesh->AddIndexQuad(6, 4, 2, 0);
					mesh->AddIndexQuad(1, 5, 3, 7);
					mesh->AddIndexQuad(5, 1, 4, 0);
					mesh->AddIndexQuad(2, 3, 6, 7);
					mesh->SetUsesTriangleFaces(true);
				};
				void Create_Cube(Mesh* mesh, float scale, Point3D center)
				{
					mesh->Clear();
					Vertex v1 = { center.GetX() - scale, center.GetY() + scale, center.GetZ() - scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0 };
					Vertex v2 = {center.GetX()-scale, center.GetY()-scale, center.GetZ()-scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					Vertex v3 = {center.GetX()+scale, center.GetY()+scale, center.GetZ()-scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					Vertex v4 = {center.GetX()+scale, center.GetY()-scale, center.GetZ()-scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					Vertex v5 = {center.GetX()-scale, center.GetY()+scale, center.GetZ()+scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					Vertex v6 = {center.GetX()-scale, center.GetY()-scale, center.GetZ()+scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					Vertex v7 = {center.GetX()+scale, center.GetY()+scale, center.GetZ()+scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					Vertex v8 = {center.GetX()+scale, center.GetY()-scale, center.GetZ()+scale, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					mesh->AddVertexQuad(v1, v2, v3, v4);
					mesh->AddVertex(v5);
					mesh->AddVertex(v6);
					mesh->AddVertex(v7);
					mesh->AddVertex(v8);
					mesh->AddIndexQuad(7, 5, 6, 4);
					mesh->AddIndexQuad(6, 4, 2, 0);
					mesh->AddIndexQuad(1, 5, 3, 7);
					mesh->AddIndexQuad(5, 1, 4, 0);
					mesh->AddIndexQuad(2, 3, 6, 7);
					mesh->SetUsesTriangleFaces(true);
				};
			};
		};
	};
};

#endif