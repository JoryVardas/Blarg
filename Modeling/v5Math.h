//
#ifndef __v5MATH_H__
#define __v5MATH_H__

#include "Global_Variables.h"
#include "v5Error.h"
#include "Vertex.h"
#include "Vector.h"
#include "Point.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			using namespace BrokenTechStudios::Nuke::Core;

			float CalculateDistance(Vertex* vertexA, Vertex* vertexB)
			{
				float x = vertexB->X - vertexA->X;
				float y = vertexB->Y - vertexA->Y;
				float z = vertexB->Z - vertexA->Z;
				
				return sqrt((x * x) + (y * y) + (z * z));
			};

			static float Average(float a, float b)
			{
				return (a + b) / 2;
			};

			void MultiplyVertexByMatrix(Vertex* vertexIn, Vertex* vertexOut, D3DXMATRIX* matrix)
			{
				vertexOut->X = (vertexIn->X * matrix->_11) + (vertexIn->Y * matrix->_21) + (vertexIn->Z * matrix->_31) + matrix->_41;
				vertexOut->Y = (vertexIn->X * matrix->_12) + (vertexIn->Y * matrix->_22) + (vertexIn->Z * matrix->_32) + matrix->_42;
				vertexOut->Z = (vertexIn->X * matrix->_13) + (vertexIn->Y * matrix->_23) + (vertexIn->Z * matrix->_33) + matrix->_43;
				vertexOut->U = vertexIn->U;
				vertexOut->V = vertexIn->V;
				vertexOut->Color = vertexIn->Color;
			};
			Point3D	MultiplyPointByMatrix (Point3D& point, D3DXMATRIX* matrix)
			{
				return Point3D((point.GetX() * matrix->_11) + (point.GetY() * matrix->_21) + (point.GetZ() * matrix->_31) + matrix->_41,
								(point.GetX() * matrix->_12) + (point.GetY() * matrix->_22) + (point.GetZ() * matrix->_32) + matrix->_42,
								(point.GetX() * matrix->_13) + (point.GetY() * matrix->_23) + (point.GetZ() * matrix->_33) + matrix->_43);
			};
			void MultiplyVectorByMatrix	(Vector* vecIn, Vector* vecOut, D3DXMATRIX* matrix)	
			{
				
				vecOut->dirX = ((vecIn->dirX * matrix->_11) + (vecIn->dirY * matrix->_21) + (vecIn->dirZ * matrix->_31) + matrix->_41);
				vecOut->dirY = ((vecIn->dirX * matrix->_12) + (vecIn->dirY * matrix->_22) + (vecIn->dirZ * matrix->_32) + matrix->_42);
				vecOut->dirZ = ((vecIn->dirX * matrix->_13) + (vecIn->dirY * matrix->_23) + (vecIn->dirZ * matrix->_33) + matrix->_43);
			};
			/*float Det (Vector** matrix3x3)
			{
				return ((matrix3x3[0]->GetX() * matrix3x3[1]->GetY() * matrix3x3[2]->GetZ()) + (matrix3x3[0]->GetY() * matrix3x3[1]->GetZ() * matrix3x3[2]->GetX()) + (matrix3x3[0]->GetZ() * matrix3x3[1]->GetX() * matrix3x3[2]->GetY()) - (matrix3x3[2]->GetX() * matrix3x3[1]->GetY() * matrix3x3[0]->GetZ()) - (matrix3x3[2]->GetY() * matrix3x3[1]->GetZ() * matrix3x3[0]->GetX()) - (matrix3x3[2]->GetZ() * matrix3x3[1]->GetX() *matrix3x3[2]->GetY()));
			};*/
			Vector** Inverse (Vector** matrix3x3)
			{
				//needs to be defined!!
				Vector v(0, 0, 0);
				Vector* v1 = &v;
				return &v1;
			};
			/*void VectorArrayToMatrix (Vector** vectorArryIn, D3DXMATRIX* matrixOut)
			{
				D3DXMATRIX mat(vectorArryIn[0]->GetX(), vectorArryIn[0]->GetY(), vectorArryIn[0]->GetZ(), 0, vectorArryIn[1]->GetX(), vectorArryIn[1]->GetY(), vectorArryIn[1]->GetZ(), 0, vectorArryIn[2]->GetX(), vectorArryIn[2]->GetY(), vectorArryIn[2]->GetZ(), 0, 0, 0, 0, 1);
				matrixOut = &mat;
			};*/
		};
	};
};
#endif