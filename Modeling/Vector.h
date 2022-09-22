//DONE
#ifndef __VECTOR_H__
#define	__VECTOR_H__

#include "Global_Variables.h"
#include "v5Error.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			using namespace BrokenTechStudios::Nuke::Core;

			//A vector has no begining or end, it is infinite.
			struct Vector
			{
				float dirX, dirY, dirZ;
				//float pX, pY, pZ;

				Vector()
				{
					dirX = dirY = dirZ = /*pX = pY = pZ = */null;
				};
				Vector(/*float px, float py, float pz, */float dirx, float diry, float dirz)
				{
					dirX = dirx;
					dirY = diry;
					dirZ = dirz;
					//pX = px;
					//pY = py;
					//pZ = pz;
				};
				Vector(float p1X, float p1Y, float p1Z, float p2X, float p2Y, float p2Z)
				{
					dirX = p2X - p1X;
					dirY = p2Y - p1Y;
					dirZ = p2Z - p1Z;
					//pX = p1X;
					//pY = p1Y;
					//pZ = p1Z;
				};
				//Vector(float dirx, float diry, float dirz)
				//{
				//	dirX = dirX;
				//	dirY = dirY;
				//	dirZ = dirZ;
				//	//pX = pY = pZ = null;
				//};
				Vector(Vector& v)
				{
					dirX = v.dirX;
					dirY = v.dirY;
					dirZ = v.dirZ;
					//pX = v.pX;
					//pY = v.pY;
					//pZ = v.pZ;
				};

				~Vector()
				{
					dirX = dirY = dirZ = /*pX = pY = pZ = */null;
				};

				void operator =(Vector& v)
				{
					dirX = v.dirX;
					dirY = v.dirY;
					dirZ = v.dirZ;
				};

				static Vector CrossProduct(Vector v1, Vector v2)
				{
					float a = v1.dirX;// +v1.pX;
					float b = v1.dirY;// +v1.pY;
					float c = v1.dirZ;// +v1.pZ;
					float d = v2.dirX;// +v2.pX;
					float e = v2.dirY;// +v2.pY;
					float f = v2.dirZ;// +v2.pZ;
					return Vector((b*f) - (c*e), (c*d) - (a*f), (a*e) - (b*d));
				};

				static float DotProduct(Vector v1, Vector v2)
				{
					//float xx = (v1.dirX + v1.pX) * (v2.dirX + v2.pX);
					//float yy = (v1.dirY + v1.pY) * (v2.dirY + v2.pY);
					//float zz = (v1.dirZ + v1.pZ) * (v2.dirZ + v2.pZ);
					float xx = (v1.dirX) * (v2.dirX);
					float yy = (v1.dirY) * (v2.dirY);
					float zz = (v1.dirZ) * (v2.dirZ);
					return xx + yy + zz;
				};
			};
		};
	};
};
#endif