//
#ifndef __RAY_H__
#define __RAY_H__

#include "v5Error.h"
#include "Global_Variables.h"
#include "Vertex.h"
#include "Point.h"
#include "Vector.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			using namespace BrokenTechStudios::Nuke::Core;

			struct Ray
			{
				float 	_DirectionX, _DirectionY, _DirectionZ;
				float 	_OriginX, _OriginY, _OriginZ;
	
				Ray(Ray& r){
					_DirectionX = r._DirectionX;
					_DirectionY = r._DirectionY;
					_DirectionZ = r._DirectionZ;
					_OriginX = r._OriginX;
					_OriginY = r._OriginY;
					_OriginZ = r._OriginZ;
				};
						Ray();
						Ray(Point3D origin, Vector direction);
						Ray(Point3D origin, float directionX, float directionY, float directionZ);
						Ray(Vertex origin, Vector direction);
						Ray(Vertex origin, float directinoX, float directionY, float directionZ);
						Ray(float originX, float originY, float originZ, float directionX, float directionY, float directionZ);
						~Ray();
	
				float 	GetDirectionX();
				float 	GetDirectionY();
				float 	GetDirectionZ();
				Point3D GetOrigin();
				float 	GetOriginX();
				float 	GetOriginY();
				float 	GetOriginZ();
				float 	GetDistanceFactorOfPoint(Point3D point);
				float 	GetDistanceFactorOfPoint(Vertex vertex);
				void 	SetDirectionX(float);
				void 	SetDirectionY(float);
				void 	SetDirectionZ(float);
				void 	SetOriginX(float);
				void 	SetOriginY(float);
				void 	SetOriginZ(float);
	
				void 	Normalize();
				bool 	IsPointOnRay(Point3D point);
				bool 	IsVertexOnRay(Vertex vertex);
				void 	Invert();
	
				Ray 	operator +(Ray&);
				Ray 	operator -(Ray&);
				Ray 	operator *(Ray&);
				Ray 	operator /(Ray&);
	
				Ray 	operator +(float);
				Ray 	operator -(float);
				Ray 	operator *(float);
				Ray 	operator /(float);
	
				Vertex 	operator +(Vertex&);
				Vertex	operator -(Vertex&);
				Vertex 	operator *(Vertex&);
				Vertex 	operator /(Vertex&);
	
				void 	operator +=(Ray&);
				void 	operator -=(Ray&);
				void 	operator *=(Ray&);
				void 	operator /=(Ray&);
	
				void 	operator +=(float);
				void 	operator -=(float);
				void 	operator *=(float);
				void 	operator /=(float);
	
				bool 	operator ==(Ray&);
				bool 	operator !=(Ray&);
				
				void 	operator =(Ray&);
				void 	operator =(float);
			};
		};
	};
};
#endif