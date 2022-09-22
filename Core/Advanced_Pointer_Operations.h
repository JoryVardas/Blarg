//DONE
#ifndef __ADVANCED_POINTER_OPERATIONS_H__
#define __ADVANCED_POINTER_OPERATIONS_H__

#include "Global_Variables.h"
#include "v5Error.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{

			void* PointerDataPartialCopy(void* pointerToData, int sizeToCopy);
			void* IncrementPointer(void* ptr);
			void* DecrementPointer(void* ptr);
			void* IncreasePointer(void* ptr, int number);
			void* DecreasePointer(void* ptr, int number);
		};
	};
};
#endif