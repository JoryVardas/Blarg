#ifndef __POINT_H__
#define __POINT_H__

#include "Vertex.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{

			using namespace BrokenTechStudios::Nuke::Core;

			class Point3D
			{
			private:
				float _X, _Y, _Z;

			public:
				Point3D(Point3D& p){
					_X = p._X;
					_Y = p._Y;
					_Z = p._Z;
				};
				Point3D(){
					_X = _Y = _Z = 0;
				};
				Point3D(float x, float y, float z){
					_X = x;
					_Y = y;
					_Z = z;
				};
				Point3D(Vertex* v){
					_X = v->X;
					_Y = v->Y;
					_Z = v->Z;
				};
				Point3D(Vertex& v){
					_X = v.X;
					_Y = v.Y;
					_Z = v.Z;
				};
				~Point3D(){
					_X = _Y = _Z = 0;
				};

				float GetX(){return _X;};
				float GetY(){return _Y;};
				float GetZ(){return _Z;};
				void SetX(float f){_X = f;};
				void SetY(float f){_Y = f;};
				void SetZ(float f){_Z = f;};

				Vertex ToVertex(){
					Vertex v = {_X, _Y, _Z, 0, 0, __WIREFRAME_VERTEX_DEFAULT_COLOR__};
					return v;
				};

				void operator =(Point3D& p)
				{
					_X = p._X;
					_Y = p._Y;
					_Z = p._Z;
				};
				void operator =(float f){
					_X = _Y = _Z = f;
				};
				bool operator ==(Point3D& p){
					return (_X == p._X) && (_Y == p._Y) && (_Z == p._Z);
				};
				bool operator !=(Point3D& p){
					return (_X != p._X) || (_Y != p._Y) || (_Z != p._Z);
				};

				Point3D operator -(Point3D& p){
					return Point3D(_X - p._X, _Y - p._Y, _Z - p._Z);
				};
			};
		};
	};
};
#endif