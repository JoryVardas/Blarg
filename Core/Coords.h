#include "Global_Variables.h"

#ifndef __COORDS_H__
#define __COORDS_H__
namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			struct Coordinates
			{
				float X, Y;

				Coordinates()
				{
					X = Y = 0;
				};
				Coordinates(Coordinates& a)
				{
					X = a.X;
					Y = a.Y;
				};
				Coordinates(float x, float y)
				{
					X = x;
					Y = y;
				};
				~Coordinates()
				{
					X = Y = 0;
				};
				void operator =(Coordinates& a)
				{
					X = a.X;
					Y = a.Y;
				};
				void operator =(float* floatArray)
				{
					X = floatArray[0];
					Y = floatArray[1];
				};
			};
		};
	};
};

#endif