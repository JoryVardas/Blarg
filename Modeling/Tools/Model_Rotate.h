#include "Mesh.h"
#include "Vertex_Rotate.h"

#ifndef __MODEL_ROTATE_H__
#define __MODEL_ROTATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Model_Rotate(Mesh* mesh, float x, float y, float z)
				{
					Point3D origin (0, 0, 0);
					int number = mesh->GetNumberOfVertices();
					for(int i = 0; i < number; i++)
					{
						Vertex_Rotate(mesh->GetVertex(i), origin, x, y, z);
					};
					/*int number2 = mesh->_VertexRendererVertexArray.GetSize();
					for(int i = 0; i < number2; i++)
					{
						Vertex_Rotate(mesh->_VertexRendererVertexArray.GetData(i), origin, x, y, z);
					};*/
				};

				static void Model_Rotate(Mesh* mesh, Point3D rotationCenter, float x, float y, float z)
				{
					for(int i = 0; i < mesh->GetNumberOfVertices(); i++)
					{
						Vertex_Rotate(mesh->GetVertex(i), rotationCenter, x, y, z);
					};
					/*int number2 = mesh->_VertexRendererVertexArray.GetSize();
					for(int i = 0; i < number2; i++)
					{
						Vertex_Rotate(mesh->_VertexRendererVertexArray.GetData(i), rotationCenter, x, y, z);
					};*/
				};
			};
		};
	};
};
#endif