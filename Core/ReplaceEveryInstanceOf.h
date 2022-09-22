#include "Array.h"

#ifndef __REPLACE_EVERY_INSTANCE_OF__
#define __REPLACE_EVERY_INSTANCE_OF__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			static void Replace_Every_Instance_Of(WORD* a, unsigned int size, WORD find, WORD replace)
			{
				Array<unsigned int> locations;
				for(unsigned int i = 0; i < size; i++)
				{
					if(a[i] == find)
					{
						a[i] = replace;
						locations.Add(i);
					};
				};
			};

			static Array<unsigned int> Replace_Every_Instance_Of(WORD* a, unsigned int size, WORD find, WORD replace, bool returnLocations)
			{
				Array<unsigned int> locations;
				for(unsigned int i = 0; i < size; i++)
				{
					if(a[i] == find)
					{
						a[i] = replace;
						locations.Add(i);
					};
				};
				return locations;
			};
		};
	};
};

#endif