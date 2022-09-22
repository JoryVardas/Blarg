#include "Mesh.h"

#ifndef __CREATE_SPHERE_H__
#define __CREATE_SPHERE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				using namespace BrokenTechStudios::Nuke::Core;
				
				static void CreateSphere(Mesh* mesh, int numberOfRows, int numberOfCollums, float scale)
				{
					Array<Vertex> verts;
					for(float theta = 0; theta < M_PI; theta += M_PI / numberOfRows)
					{
						float y = scale * cos(theta);
						for(float alpha = 0; alpha < 2 * M_PI; alpha += (2 * M_PI) / numberOfCollums)
						{
							float x = scale * cos(alpha) * sin(theta);
							float z = scale * sin(alpha) * sin(theta);

							//float z = 0;
							//float y = scale * sin(alpha);
							if(z != 0 || x != 0){
							Vertex v = {x, y, z, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
							verts.Add(v);
							};
						};
					};
					Vertex vert = {0, -scale, 0, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					Vertex vert2 = {0, scale, 0, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
					verts.Add(vert);
					verts.Add(vert2);
					mesh->SetVertexArray(verts.GetDataActual());
					for(int i = 0; i < verts.GetSize() - numberOfCollums - 2; i++)
					{
						mesh->AddIndexTriangle(i, i+1, i+numberOfCollums);
						mesh->AddIndexTriangle(i+1, i+numberOfCollums+1, i+numberOfCollums);
						//inds.Add(i);
						//inds.Add(i+1);
						//inds.Add(i+numberOfCollums);
					};
					for(int i = verts.GetSize() - numberOfCollums - 2; i < verts.GetSize() - 2; i++)
					{
						mesh->AddIndexTriangle(i, i+1, verts.GetSize() - 2);
						//inds.Add(i);
						//inds.Add(i+1);
						//inds.Add(verts.GetSize() - 2);
					};
					for(int i = 0; i < numberOfCollums - 1; i++)
					{
						mesh->AddIndexTriangle(i+1, i, verts.GetSize() - 1);
						//inds.Add(verts.GetSize() - 1);
						//inds.Add(i);
						//inds.Add(i+1);
					};
					mesh->AddIndexTriangle(0, numberOfCollums - 1, verts.GetSize() - 1);
					mesh->AddIndexTriangle(numberOfCollums - 1, 0, numberOfCollums);
					mesh->SetUsesTriangleFaces(true);
				};
				static void CreateSphere(Mesh* mesh, Point3D center, int numberOfRows, int numberOfCollums, float scale)
				{
					Array<Vertex> verts;
					float thetaInterval = M_PI / numberOfRows;
					float alphaInterval = M_PI / numberOfCollums;
					for(int r = 0; r < numberOfRows; r++)
					{
						float theta = thetaInterval * r;
						for(int c = 0; c < numberOfCollums; c++)
						{
							float alpha = alphaInterval * c;
							float x = scale * cos(alpha);
							float y = scale * sin(theta);
							float z = scale * sin(alpha);
							Vertex v = {x + center.GetX(), y + center.GetY(), z + center.GetZ(), 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
							verts.Add(v);
						};
					};
					mesh->SetVertexArray(verts.GetDataActual());
					for(int r = 0; r < numberOfRows - 1; r++)
					{
						for(int c = 0; c < numberOfCollums; c++)
						{
							uint index1 = (r * numberOfCollums) + c;
							uint index2 = (r * numberOfCollums) + c + 1;
							uint index3 = ((r + 1) * numberOfCollums) + c;
							uint index4 = ((r + 1) * numberOfCollums) + c + 1;
							mesh->AddIndexQuad(index1, index2, index3, index4);
						};
					};
					mesh->SetUsesTriangleFaces(true);
				};
			};
		};
	};
};

#endif