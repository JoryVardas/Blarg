#include "Mesh.h"
#include "Vertex_Rotate.h"

#ifndef __CREATE_TORUS_H__
#define __CREATE_TORUS_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				using namespace BrokenTechStudios::Nuke::Core;

				static void CreateTorus(Mesh* mesh, float torusRadius, float innerRadius, float numberOfCollums, float numberOfRows)
				{
					Array<Vertex> verts;
					float thetaInterval = 2 * M_PI / numberOfCollums;
					float alphaInterval = 2 * M_PI / numberOfRows;
					for(int c = 0; c < numberOfCollums; c++)
					{
						float theta = thetaInterval * c;
						for(int r = 0; r < numberOfRows; r++)
						{
							float alpha = alphaInterval * r;
							float x = innerRadius * cos(alpha);
							float y = innerRadius * sin(alpha);
							Vertex v = {x + torusRadius, y, 0, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__, 0};
							Vertex_Rotate(&v, Point3D(0, 0, 0), 0, theta, 0);
							verts.Add(v);
						};
					};
					mesh->SetVertexArray(verts.GetDataActual());

					for(int c = 0; c < numberOfCollums - 1; c++)
					{
						for(int r = 0; r < numberOfRows - 1; r++)
						{
							uint index1 = (c * numberOfRows) + r;
							uint index2 = (c * numberOfRows) + r + 1;
							uint index3 = ((c + 1) * numberOfRows) + r;
							uint index4 = ((c + 1) * numberOfRows) + r + 1;
							mesh->AddIndexQuad(index1, index2, index3, index4);
						};
					};
					for(int c = 0; c < numberOfCollums - 1; c++)
					{
						uint index1 = (c * numberOfRows);
						uint index2 = (c * numberOfRows) + numberOfRows - 1;
						uint index3 = ((c + 1) * numberOfRows);
						uint index4 = ((c + 1) * numberOfRows) + numberOfRows - 1;
						mesh->AddIndexQuad(index1, index3, index2, index4);
					};
					for(int r = 0; r < numberOfRows - 1; r++)
					{
						uint index1 = ((numberOfCollums - 1) * numberOfRows) + r;
						uint index2 = ((numberOfCollums - 1) * numberOfRows) + r + 1;
						uint index3 = r;
						uint index4 = r + 1;
						mesh->AddIndexQuad(index1, index2, index3, index4);
					};
					mesh->AddIndexQuad(((numberOfCollums - 1) * numberOfRows) + numberOfRows -1, ((numberOfCollums - 1) * numberOfRows), numberOfRows - 1, 0);
					
					mesh->SetUsesTriangleFaces(true);
				};
			};
		};
	};
};

#endif