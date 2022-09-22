//DONE

#ifndef __GLOBAL_VARIABLES_H__
#define __GLOBAL_VARIABLES_H__

#include "Base_Includes.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			#define null 0
			#define __FILE_GET_LINE_DELIMINATING_CHARACTER__ '\n'
			#define __DEFUALT_INT_TO_STRING_SIZE__ 6
			#define __DEFUALT_FLOAT_TO_STRING_SIZE__ 10
			#define v5Polygon BrokenTechStudios::Nuke::_3DModeling::Polygon
			#define __DIRECTX_NAMESPACE_START__ namespace BrokenTechStudios { namespace Nuke { namespace Rendering { namespace DirectX {
			#define __DIRECTX_NAMESPACE_END__	}; }; }; };
			#define __USING_CORE__ using namespace BrokenTechStudios::Nuke::Core;
			#define __USING_UI__ using namespace BrokenTechStudios::Nuke::UI;
			#define __USING_DIRECTX__ using namespace BrokenTechStudios::Nuke::Rendering::DirectX;
			#define __USING_3DMODELING__ using namespace BrokenTechStudios::Nuke::_3DModeling;
			#define __WIREFRAME_VERTEX_DEFAULT_COLOR__ D3DXCOLOR(0.3, 0.3, 1, 1)
			#define __WIREFRAME_VERTEX_SELECTED_COLOR__ D3DXCOLOR(0.3, 0, 0, 1)

			//used for event handeling
			#define EventHandler(name) void (*name)(void*)
			#define EventHandlerFunction void(*)(void*)
			#define Event(name) void(*name)()
			#define EventFunction void(*)()
			#define CallEventHandlers(Array, eventDataPtr) for(int i = 0; i < Array.GetSize(); i++){ \
															EventHandler(function) = (EventHandlerFunction)Array[i].GetData(); \
															function((void*)eventDataPtr);}
			#define EventHandlerList(name) Array<uint> name
			//void pointer
			#define vptr(var) (void*)(var)

			//used to allow chained methods.  name is the object that the method is a part of.
			#define chained(type) type&
			#define chainedReturn return *this
			#define __MEMORY_CHECK__ if(__ALLOW_MEMORY_CHECKS__){ \
									 char* __MEMORY_CHECK_CHARACTER_ARRAY__ = new char[2]; \
									 delete[] __MEMORY_CHECK_CHARACTER_ARRAY__;};
			typedef unsigned int uint;

			////////////////////////////////////////////////////////////
			static bool __ALLOW_MEMORY_CHECKS__ = true;
			static bool	__IS_EXITING__ = false;
			static int	__EXITING_CODE__ = 0;
			static int	__NUMBER_OF_ERRORS__ = 0;
			static int	__SCREEN_WIDTH__ = 600;
			static int	__SCREEN_HEIGHT__ = 600;
			static int __RENDER_WINDOW_WIDTH__ = 600;
			static int __RENDER_WINDOW_HEIGHT__ = 600;
			static int	__NEXT_ERROR_ID__ = 0;
			static char* __ERROR_DIRECTORY__	= "C:\\Users\\Joshua\\Desktop\\Nuke\\ErrorFolder";
			static int	__POSITION_X__ = 100;
			static int	__POSITION_Y__ = 100;
			static bool __WINDOWED__ = true;
			static unsigned int __MEMORY_POINTERS_TO_RELEASE_UPON_EXITING__ [500];
			static int __MEMORY_POINTERS_TO_RELEASE_UPON_EXITING_INDEX__ = 0;
			static int __PAUSE_FOR_SCRIPT_MODIFICATION_OF_VARIABLES__ = false;
			static float __CURRENT_BRUSH_LOCATION_X__ = 0;
			static float __CURRENT_BRUSH_LOCATION_Y__ = 0;
			static char* __TEMPARARY_OBJECT_FOLDER__ = "C:\\Users\\Joshua\\Desktop\\Nuke\\TempararyObjectFolder";
			static int __NEXT_AVAILABLE_TEMPARARY_OBJECT_NUMBER__ = -1;
			//static D3DXCOLOR __DEFAULT_VERTEX_COLOR__ = D3DXCOLOR(1, 1, 1, 1);
			static uint __CORE_EVENTS_TO_CHECK__[100];//max size is meerely for memory conservation.
			static uint __CORE_EVENTS_TO_CHECK_ARRAY_NEXT_INDEX__ = 0;
			
			static char __INT_TO_STRING_CHAR_ARRAY[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
			

			////////////////////////////////////////////////////////////

			static bool __ADD_CORE_EVENT_TO_CHECK__(uint eventCheckFunctionAddress)
			{
				if(__CORE_EVENTS_TO_CHECK_ARRAY_NEXT_INDEX__ == 99) return false;
				__CORE_EVENTS_TO_CHECK__[__CORE_EVENTS_TO_CHECK_ARRAY_NEXT_INDEX__] = eventCheckFunctionAddress;
				__CORE_EVENTS_TO_CHECK_ARRAY_NEXT_INDEX__++;
				return true;
			};

			//should be called in the main loop of the program
			static void __CHECK_CORE_EVENTS__()
			{
				for(uint i = 0; i < __CORE_EVENTS_TO_CHECK_ARRAY_NEXT_INDEX__; i++)
				{
					Event(function) = (EventFunction)__CORE_EVENTS_TO_CHECK__[i];
					function();
				};
			};

			static int	__GET_NEXT_ERROR_ID__()
			{
				int tempErrorID = __NEXT_ERROR_ID__;
				__NEXT_ERROR_ID__++;
				return tempErrorID;
			};

			static void __SET_DATA_FOR_RELEASE_UPON_EXITING__(unsigned int addressOfString)
			{
				__MEMORY_POINTERS_TO_RELEASE_UPON_EXITING__[__MEMORY_POINTERS_TO_RELEASE_UPON_EXITING_INDEX__] = addressOfString;
				__MEMORY_POINTERS_TO_RELEASE_UPON_EXITING_INDEX__++;
			};

			static int __GET_NEXT_AVAILABLE_TEMPARARY_OBJECT_NUMBER__()
			{
				__NEXT_AVAILABLE_TEMPARARY_OBJECT_NUMBER__++;
				return __NEXT_AVAILABLE_TEMPARARY_OBJECT_NUMBER__;
			};

			static void __RELEASE_STORED_DATA_UPON_EXITING__()
			{
				for(int i = 0; i < __MEMORY_POINTERS_TO_RELEASE_UPON_EXITING_INDEX__; i++)
				{
					delete (void*)__MEMORY_POINTERS_TO_RELEASE_UPON_EXITING__[i];
				};
			};

			static void __TRY_DELETE_C_STRING__(char* str)
			{
				delete[] str;
			};

			template <typename T>
			static void __TRY_DELETE_C_ARRAY__(T* a)
			{
				delete[] a;
			};

			static unsigned int __GET_C_STRING_SIZE__(char* str)
			{
				unsigned int i = 0;
				while(true)
				{
					if(str[i] == '\0')
					{
						return i + 1;
					}
					else
					{
						i++;
					};
				};
			};
		    
			template <typename T>
			static void __ADD_C_ARRAY__(T* a, unsigned int sizeA, T* b, unsigned int sizeB)
			{
				__RESIZE_ARRAY(a, sizeA, sizeA + sizeB);//a = (T*)realloc(a, sizeA + sizeB);
				for(int i = 0; i < sizeB; i++)
				{
					a[sizeA + i] = b[i];
				};
			};
			
			static bool div0(float x)
			{
				return (_isnan(x) || (x == FLT_MAX) || (x == FLT_MIN));
			};

			template <typename T>
			static inline void __RESIZE_ARRAY__(T* arrayPtr, uint arraySize, T** dest, uint newSize){
				T* newArray = new T[newSize];
				for(uint i = 0; i < arraySize; i++){
					newArray[i] = arrayPtr[i];
				};
				delete[] newArray;
				*dest = newArray;
			};

			template<typename T>
			static void __COPY_ARRAY__(T* dest, T* source, uint numberOfElements)
			{
				for(int i = 0; i < numberOfElements; i++)
				{
					dest[i] = source[i];
				};
			};
		};
	};
};

#endif