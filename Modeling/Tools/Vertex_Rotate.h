#include "Vertex.h"
#include "Point.h"
#include "v5Math.h"

#ifndef __VERTEX_ROTATE_H__
#define __VERTEX_ROTATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Vertex_Rotate(Vertex* vert, Point3D rotationCenter, float x, float y, float z)
				{
					D3DXMATRIX rotMat;
					D3DXMATRIX rotMatx;
					D3DXMATRIX rotMaty;
					D3DXMATRIX rotMatz;
					D3DXMatrixIdentity(&rotMat);
					D3DXMatrixRotationX(&rotMatx, x);
					D3DXMatrixRotationY(&rotMaty, y);
					D3DXMatrixRotationZ(&rotMatz, z);
					rotMat = rotMat * rotMatx * rotMaty * rotMatz;
					Vertex v1 = *vert;
					v1.X -= rotationCenter.GetX();
					v1.Y -= rotationCenter.GetY();
					v1.Z -= rotationCenter.GetZ();
					MultiplyVertexByMatrix(&v1, vert, &rotMat);
					vert->X += rotationCenter.GetX();
					vert->Y += rotationCenter.GetY();
					vert->Z += rotationCenter.GetZ();
				};
				static void Vertex_Rotate(Vertex* vert, float x, float y, float z)
				{
					D3DXMATRIX rotMat;
					D3DXMATRIX rotMatx;
					D3DXMATRIX rotMaty;
					D3DXMATRIX rotMatz;
					D3DXMatrixIdentity(&rotMat);
					D3DXMatrixRotationX(&rotMatx, x);
					D3DXMatrixRotationY(&rotMaty, y);
					D3DXMatrixRotationZ(&rotMatz, z);
					rotMat = rotMat * rotMatx * rotMaty * rotMatz;
					Vertex v1 = *vert;
					MultiplyVertexByMatrix(&v1, vert, &rotMat);
				};
			};
		};
	};
};

#endif