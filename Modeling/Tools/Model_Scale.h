#include "Mesh.h"
#include "Vertex_Scale.h"

#ifndef __MODEL_SCALE_H__
#define __MODEL_SCALE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Model_Scale(Mesh* mesh, float factor)
				{
					Point3D origin (0, 0, 0);
					for(int i = 0; i < mesh->GetNumberOfVertices(); i++)
					{
						Vertex_Scale(mesh->GetVertexArrayDirect()[i], origin, factor);
					};
					/*for(int i = 0; i < mesh->_VertexRendererVertexArray.GetSize(); i++)
					{
						Vertex_Scale(mesh->_VertexRendererVertexArray.GetData(i), origin, factor);
					};*/
				};

				static void Model_Scale(Mesh* mesh, Point3D rotationCenter, float factor)
				{
					for(int i = 0; i < mesh->GetNumberOfVertices(); i++)
					{
						Vertex_Scale(mesh->GetVertexArrayDirect()[i], rotationCenter, factor);
					};
					/*for(int i = 0; i < mesh->_VertexRendererVertexArray.GetSize(); i++)
					{
						Vertex_Scale(mesh->_VertexRendererVertexArray.GetData(i), rotationCenter, factor);
					};*/
				};
				
				static void Model_Scale(Mesh* mesh, Point3D rotationCenter, float x, float y, float z)
				{
					for(int i = 0; i < mesh->GetNumberOfVertices(); i++)
					{
						Vertex_Scale(mesh->GetVertexArrayDirect()[i], rotationCenter, x, y, z);
					};
					/*for(int i = 0; i < mesh->_VertexRendererVertexArray.GetSize(); i++)
					{
						Vertex_Scale(mesh->_VertexRendererVertexArray.GetData(i), rotationCenter, x, y, z);
					};*/
				};

				static void Model_Scale(Mesh* mesh, float x, float y, float z, bool useMeshCenter)
				{
					uint number = mesh->GetNumberOfVertices();
					for(int i = 0; i < number; i++)
					{
						Vertex_Scale(mesh->GetVertexArrayDirect()[i], Point3D(mesh->_X, mesh->_Y, mesh->_Z), x, y, z);
					};
					/*uint number2 = mesh->_VertexRendererVertexArray.GetSize();
					for(int i = 0; i < number2; i++)
					{
						Vertex_Scale(mesh->_VertexRendererVertexArray.GetData(i), Point3D(mesh->_X, mesh->_Y, mesh->_Z), x, y, z);
					};*/
				};
			};
		};
	};
};
#endif