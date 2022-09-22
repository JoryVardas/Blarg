#include "Global_Variables.h"
#include "Vertex.h"
#include "Vector.h"

#ifndef __TRIANGLE_FACE_H__
#define __TRIANGLE_FACE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			struct TriangleFace
			{
				Vertex* _Vertex1;
				Vertex* _Vertex2;
				Vertex* _Vertex3;

				TriangleFace(){
					_Vertex1 = _Vertex2 = _Vertex3 = null;
				};
				TriangleFace(TriangleFace& f){
					_Vertex1 = f._Vertex1;
					_Vertex2 = f._Vertex2;
					_Vertex3 = f._Vertex3;
				};
				TriangleFace(Vertex* v1, Vertex* v2, Vertex* v3){
					_Vertex1 = v1;
					_Vertex2 = v2;
					_Vertex3 = v3;
				};
				~TriangleFace(){
					_Vertex1 = _Vertex2 = _Vertex3 = null;
				};
				Vertex* GetVertex1(){
					return _Vertex1;
				};
				Vertex* GetVertex2(){
					return _Vertex2;
				};
				Vertex* GetVertex3(){
					return _Vertex3;
				};

				bool GetClickTriangleFaceIntersection(Point3D click){
					float py = click.GetY();
					float px = click.GetX();
					float ax = _Vertex2->X - _Vertex1->X;
					float ay = _Vertex2->Y - _Vertex1->Y;
					float ox = _Vertex1->X;
					float oy = _Vertex1->Y;
					float bx = _Vertex3->X - _Vertex1->X;
					float by = _Vertex3->Y - _Vertex1->Y;

					float alpha = ((py*ax)-(oy*ax)-(px*ay)+(ox*ay))/((by*ax)-(bx*ay));
					float beta = ((py*bx)-(oy*bx)-(px*by)+(ox*by))/((ay*bx)-(ax*by));

					bool test1 =  ((alpha >= 0) && (alpha <= 1) && (beta >= 0) && (beta <= 1));

					float py2 = click.GetY();
					float px2 = click.GetX();
					float ax2 = _Vertex3->X - _Vertex2->X;
					float ay2 = _Vertex3->Y - _Vertex2->Y;
					float ox2 = _Vertex2->X;
					float oy2 = _Vertex2->Y;
					float bx2 = _Vertex1->X - _Vertex2->X;
					float by2 = _Vertex1->Y - _Vertex2->Y;
					float alpha2 = ((py*ax)-(oy*ax)-(px*ay)+(ox*ay))/((by*ax)-(bx*ay));
					float beta2 = ((py*bx)-(oy*bx)-(px*by)+(ox*by))/((ay*bx)-(ax*by));

					bool test2 =  ((alpha2 >= 0) && (alpha2 <= 1) && (beta2 >= 0) && (beta2 <= 1));
					return (test1 && test2);
				};

				Point3D GetClickFaceIntersectionPoint(Point3D click){
					float py = click.GetY();
					float px = click.GetX();
					float ax = _Vertex2->X - _Vertex1->X;
					float ay = _Vertex2->Y - _Vertex1->Y;
					float az = _Vertex2->Z - _Vertex1->Z;
					float ox = _Vertex1->X;
					float oy = _Vertex1->Y;
					float oz = _Vertex1->Z;
					float bx = _Vertex3->X - _Vertex1->X;
					float by = _Vertex3->Y - _Vertex1->Y;
					float bz = _Vertex3->Z - _Vertex1->Z;
					
					float alpha = ((py*ax)-(oy*ax)-(px*ay)+(ox*ay))/((by*ax)-(bx*ay));
					float beta = ((py*bx)-(oy*bx)-(px*by)+(ox*by))/((ay*bx)-(ax*by));
					
					float pz = oz + (beta * az) + (alpha * bz);
					return Point3D(px, py, pz);
				};

				Point3D GetCenterPoint(){
					float ax = _Vertex2->X - _Vertex1->X;
					float ay = _Vertex2->Y - _Vertex1->Y;
					float az = _Vertex2->Z - _Vertex1->Z;
					float ox = _Vertex1->X;
					float oy = _Vertex1->Y;
					float oz = _Vertex1->Z;
					float bx = _Vertex3->X - _Vertex1->X;
					float by = _Vertex3->Y - _Vertex1->Y;
					float bz = _Vertex3->Z - _Vertex1->Z;
					float px = ox + (0.5*ax) + (0.5*bx);
					float py = oy + (0.5*ay) + (0.5*by);
					float pz = oz + (0.5*az) + (0.5*bz);
					return Point3D(px, py, pz);
				};

				void operator =(TriangleFace f)
				{
					_Vertex1 = f._Vertex1;
					_Vertex2 = f._Vertex2;
					_Vertex3 = f._Vertex3;
				};
			};
		};
	};
};

#endif