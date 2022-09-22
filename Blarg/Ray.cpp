#include "Ray.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			Ray::Ray()
			{
				_DirectionX = _DirectionY = _DirectionZ = _OriginX = _OriginY = _OriginZ = 0;
			};
			
			Ray::Ray(Point3D a, Vector d)
			{
				_OriginX = a.GetX();
				_OriginY = a.GetY();
				_OriginZ = a.GetZ();
				_DirectionX = d.dirX;
				_DirectionY = d.dirY;
				_DirectionZ = d.dirZ;
			};

			Ray::Ray(Point3D a, float x, float y, float z)
			{
				_OriginX = a.GetX();
				_OriginY = a.GetY();
				_OriginZ = a.GetZ();
				_DirectionX = x;
				_DirectionY = y;
				_DirectionZ = z;
			};
			
			Ray::Ray(Vertex a, Vector d)
			{
				_OriginX = a.X;
				_OriginY = a.Y;
				_OriginZ = a.Z;
				_DirectionX = d.dirX;
				_DirectionY = d.dirY;
				_DirectionZ = d.dirZ;
			};
			
			Ray::Ray(Vertex a, float x, float y, float z)
			{
				_OriginX = a.X;
				_OriginY = a.Y;
				_OriginZ = a.Z;
				_DirectionX = x;
				_DirectionY = y;
				_DirectionZ = z;
			};

			Ray::Ray(float a, float b, float c, float d, float e, float f)
			{
				_OriginX = a;
				_OriginY = b;
				_OriginZ = c;
				_DirectionX = d;
				_DirectionY = e;
				_DirectionZ = f;
			};

			Ray::~Ray(){};

			float Ray::GetDirectionX()
			{
				return _DirectionX;
			};

			float Ray::GetDirectionY()
			{
				return _DirectionY;
			};
			
			float Ray::GetDirectionZ()
			{
				return _DirectionZ;
			};
			
			float Ray::GetOriginX()
			{
				return _OriginX;
			};

			float Ray::GetOriginY()
			{
				return _OriginY;
			};

			float Ray::GetOriginZ()
			{
				return _OriginZ;
			};

			float Ray::GetDistanceFactorOfPoint(Point3D p)
			{
				try
				{
					float x = (p.GetX() - _OriginX) / (_DirectionX - _OriginX);
					float y = (p.GetY() - _OriginY) / (_DirectionY - _OriginY);
					float z = (p.GetY() - _OriginZ) / (_DirectionZ - _OriginZ);
					return (x + y + z) / 3;
				}
				catch(...)
				{
				};
				return null;
			};

			float Ray::GetDistanceFactorOfPoint(Vertex v)
			{
				try
				{
					float x = (v.X - _OriginX) / (_DirectionX - _OriginX);
					float y = (v.Y - _OriginY) / (_DirectionY - _OriginY);
					float z = (v.Y - _OriginZ) / (_DirectionZ - _OriginZ);
					return (x + y + z) / 3;
				}
				catch(...)
				{
				};
				return null;
			};
		};
	};
};