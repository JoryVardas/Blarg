#include "Global_Variables.h"
#include "Coords.h"
#include "v5String.h"
#include "Array.h"

#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__
namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			static Coordinates ConvertScreenCoordsToWorldCoords(Coordinates& coords, float screenWidth, float screenHight){
				//return Coordinates((((2 * coords.X) / screenWidth) - 1), (1 - ((2 * coords.Y) / screenHight)));
				float x2 = 2 * coords.X;
				float y2 = 2 * coords.Y;
				float divX = x2 / screenWidth;
				float divY = y2 / screenHight;
				float x = divX - 1;
				float y = 1 - divY;
				//if (y < 0) y -= 0.1;
				//if (x > 0) x -= 0.1;
				return Coordinates(x, y);
				//return Coordinates((coords.X / (screenWidth / 2)) - 1, (coords.Y / (screenHight / 2)) - 1);
			};

			static float ConvertXWorldToScreen(float x)
			{
				return (600 * (x + 1)) / 2;
			};
			static float ConvertYWorldToScreen(float y)
			{
				return (600 * (1 - y)) / 2;
			};


			static v5String IntToString(int i)
			{
				if(i < 0)
				{
					i = i * -1;
				};
				if(i == 0)
				{
					return "0";
				};
				Array<char> str;
				str.SetResizeAmount(1);
				while(i != 0)
				{
					str.Add(__INT_TO_STRING_CHAR_ARRAY[i % 10]);
					i = i / 10;
				};
				Array<char> ret;
				ret.SetResizeAmount(1);
				for(int i = 0; i < str.GetSize(); i++)
				{
					ret.Add(str[str.GetSize() - 1 - i].GetData());
				};
				ret.Add('\0');
				str.Clear();
				return v5String(ret.GetData().GetData(), ret.GetSize());
			};
			//might work??
			static v5String IntToString(int i, int base)
			{
				if(i < 0)
				{
					i = i * -1;
				};
				if(i == 0)
				{
					return "0";
				};
				if(base == 0 || base > 16)
				{
					return "";
				};
				Array<char> str;
				str.SetResizeAmount(1);
				while(i != 0)
				{
					str.Add(__INT_TO_STRING_CHAR_ARRAY[i % base]);
					i = i / base;
				};
				Array<char> ret;
				ret.SetResizeAmount(1);
				for(int i = 0; i < str.GetSize(); i++)
				{
					ret.Add(str[str.GetSize() - 1 - i].GetData());
				};
				ret.Add('\0');
				str.Clear();
				return v5String(ret.GetData().GetData(), ret.GetSize());
			};
		};
	};
};

#endif