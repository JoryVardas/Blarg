#include "Mesh.h"
#include "Vertex_Translate.h"

#ifndef __FACE_TRANSLATE_H__
#define __FACE_TRANSLATE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				static void Face_Translate(Face face, float x, float y, float z)
				{
					Vertex_Translate(face.GetVertex1(), x, y, z);
					Vertex_Translate(face.GetVertex2(), x, y, z);
					Vertex_Translate(face.GetVertex3(), x, y, z);
					Vertex_Translate(face.GetVertex4(), x, y, z);
				};
			};
		};
	};
};

#endif