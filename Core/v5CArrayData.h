#include "Global_Variables.h"

#ifndef __V5_C_ARRAY_DATA_H__
#define __V5_C_ARRAY_DATA_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			template <typename T>
			struct v5CArrayData
			{
				T* _Address;
				unsigned int _Length;

				v5CArrayData(v5CArrayData<T>& a){
					_Address = a._Address;
					_Length = a._Length;
				};
				v5CArrayData()
				{
					_Address = null;
					_Length = null;
				};

				v5CArrayData(T* address, unsigned int length)
				{
					_Address = address;
					_Length = length;
				};
				
				//use with exreme caution!
				v5CArrayData(T address, uint length)
				{
					*_Address = address;
					_Length = length;
				};

				~v5CArrayData()
				{
					_Address = null;
					_Length = null;
				};

				T* GetData()
				{
					return _Address;
				};

				unsigned int GetLength()
				{
					return _Length;
				};

				T* operator [](int index)
				{
					return &_Address[index];
				};

				T GetNonPointer(int index)
				{
					return _Address[index];
				};

				void operator =(v5CArrayData<T> a){
					_Address = a._Address;
					_Length = a._Length;
				};
			};

			typedef v5CArrayData<char> CharArray;
			typedef v5CArrayData<int> IntArray;
			typedef v5CArrayData<uint> UIntArray;
			typedef v5CArrayData<float> FloatArray;
		};
	};
};

#endif