#include "Mesh.h"

#ifndef __FACE_SELECT_H__
#define __FACE_SELECT_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			namespace Tools
			{
				struct FaceSelectReturnAdvanced
				{
					bool usesTriangleFaces;
					Face face;
					TriangleFace triangleFace;

					FaceSelectReturnAdvanced()
					{
						usesTriangleFaces = false;
					};
					FaceSelectReturnAdvanced(Face f)
					{
						usesTriangleFaces = false;
						face = f;
					};
					FaceSelectReturnAdvanced(TriangleFace f)
					{
						usesTriangleFaces = true;
						triangleFace = f;
					};
					~FaceSelectReturnAdvanced(){};
					void operator =(FaceSelectReturnAdvanced& f)
					{
						usesTriangleFaces = f.usesTriangleFaces;
						face = f.face;
						triangleFace = f.triangleFace;
					};
				};
				struct FaceSelectTestResult
				{
					int faceIndex;
					float distance;
				};
				int Face_Select(Mesh* mesh, float clickX, float clickY)
				{
					if (mesh->UsesTriangleFaces())
					{
						Array<FaceSelectTestResult> results;
						for (int i = 0; i < mesh->GetNumberOfFaces(); i++)
						{
							TriangleFace t = mesh->GetNthTriangleFace(i);
							D3DXVECTOR3 v0(ConvertXWorldToScreen(t.GetVertex1()->X), ConvertYWorldToScreen(t.GetVertex1()->Y), t.GetVertex1()->Z);
							D3DXVECTOR3 v1(ConvertXWorldToScreen(t.GetVertex2()->X), ConvertYWorldToScreen(t.GetVertex2()->Y), t.GetVertex2()->Z);
							D3DXVECTOR3 v2(ConvertXWorldToScreen(t.GetVertex3()->X), ConvertYWorldToScreen(t.GetVertex3()->Y), t.GetVertex3()->Z);
							D3DXVECTOR3 rayPos(clickX, clickY, 1);
							D3DXVECTOR3 rayDir(0, 0, -1);
							FLOAT outU = 0;
							FLOAT outV = 0;
							FLOAT outT = 0;

							if(D3DXIntersectTri(&v0, &v1, &v2, &rayPos, &rayDir, &outU, &outV, &outT))
							{
								FaceSelectTestResult ret = { i, outT };
								results.Add(ret);
							};
						};
						if (results.GetSize() == 0)
						{
							return -1;
						};
						FaceSelectTestResult result = results[0].GetData();
						for (int i = 1; i < results.GetSize(); i++)
						{
							if (results[i].GetData().distance < result.distance) result = results[i].GetData();
						};
						return result.faceIndex;
					};
					return -1;
				};
			};
		};
	};
};

#endif