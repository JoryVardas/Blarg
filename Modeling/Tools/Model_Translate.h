#include "Vertex_Translate.h"

#ifndef __MODEL_TRANSLATE_H__
#define __MODEL_TRANSLATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Model_Translate(Mesh* mesh, float x, float y, float z)
				{
					uint number = mesh->GetNumberOfVertices();
					for(uint i = 0; i < number; i++)
					{
						Vertex_Translate(mesh->GetVertexArrayDirect()[i], x, y, z);
					};
					/*uint number2 = mesh->_VertexRendererVertexArray.GetSize();
					for(uint i = 0; i < number2; i++)
					{
						Vertex_Translate(mesh->_VertexRendererVertexArray.GetDataActual()[i], x, y, z);
					};*/
				};
			};
		};
	};
};

#endif