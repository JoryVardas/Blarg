//DONE

#include "Global_Variables.h"
#include "v5Error.h"
#include "Reference.h"
#include "Common_Functions.h"

#ifndef __ARRAY_H__
#define __ARRAY_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			template <typename T>
			class Array
			{
			private:
				T*	_DataArray		;
				int	_Size			;
				int	_ActualSize		;
				int	_ResizeAmount		;
				int	_NextAvailableIndex	;
	
			////////////////////////////////////////////////////////////
			public:
				Array<T>(Array<T>& a)
				{
					Clear();
					
					_ResizeAmount = 5;
					_DataArray = new T[a.GetSize()];
					for(int i = 0; i < a.GetSize(); i++)
					{
						Add(*(a.GetData(i)));
					};
				};
				Array<T>()
				{
					_DataArray = null;
					_Size = 0;
					_ActualSize = 0;
					_ResizeAmount = 5;
					_NextAvailableIndex = 0;
				};

				~Array<T>()
				{
					if(_ActualSize > 0)
					{
						//try
						//{
							delete[] _DataArray;
							_DataArray = null;
						//}
						//catch(...)
						//{
						//	v5Error error (5, "An Array failed to release it's data array upon it's destruction.");
						//	error.Print();
						//}
					};
					_Size = 0;
					_ActualSize = 0;
					_ResizeAmount = 0;
				};

				v5CArrayData<T> GetData()
				{
					return v5CArrayData<T>(_DataArray, _ActualSize);
				};

				T* GetData(int index)
				{
					return &(_DataArray[index]);
				};

				//returns an array that contains no emtpy slots.  Used for rending models. use with extreme caution!
				//caused memory leak!!!
				v5CArrayData<T> GetDataActual(){
				//	if(_Size == _ActualSize) return v5CArrayData<T>(_DataArray, _Size );
				//	else{
				//		uint size = _Size * sizeof(T);
				//		T* ret = new T[_Size];
				//		memcpy(ret, _DataArray, size);
				//		return v5CArrayData<T>(ret, _Size);
				//	};
					return v5CArrayData<T>(_DataArray, _Size);
				};

				int GetSize()
				{
					__MEMORY_CHECK__
					return _Size;
				};

				int GetResizeAmount()
				{
					return _ResizeAmount;
				};

				int GetNextAvailableIndex()
				{
					return _NextAvailableIndex();
				};

				void SetData(T* a, int b)
				{
					Clear();
					_DataArray = new T[b];
					_Size = b;
					_ActualSize = b;
				};

				void SetSize(int a)
				{
					v5Error error (14, "Attempt to set the size of an array.");
					error.Print();
				};

				void SetResizeAmount(int a)
				{
					_ResizeAmount = a;
				};

				void SetNextAvailableIndex(int a)
				{
					v5Error error (14, "Attempt to set the next available index of an array.");
					error.Print();
				};

				void ResizeDataArray(int a)
				{
					try
					{
						if(_ActualSize == 0){
							_DataArray = new T[a];
						}
						else{
							T* newArray = new T[_ActualSize + a];
							for(uint i = 0; i < _ActualSize; i++){
								newArray[i] = _DataArray[i];
							};
							delete[] _DataArray;
							_DataArray = newArray;
						};
						_ActualSize += a;
					}
					catch(...)
					{
//						v5Error error (65535, "Could not resize the array's data array.");
					//	error.Print();
					};
				};

				void Add(T d)
				{
					//if(_DataArray == null)
					//{
					//	v5Error error (3);
					//	error.Print();
					//};
					if((_ActualSize - _Size) == 0)
					{
						ResizeDataArray(_ResizeAmount);
					};
					_DataArray[_NextAvailableIndex] = d;
					_NextAvailableIndex++;
					_Size++;
				};

				void Add(Array<T> a)
				{
					if((_ActualSize == _Size) < (a.GetSize() + 2))
					{
						ResizeDataArray(a.GetSize());
					};
					for(int i = 0; i < a.GetSize; i++)
					{
						Add(a.GetData(i));
					};
				};

				void AddRange(v5CArrayData<T> data)
				{
					for(int i = 0; i < data.GetLength(); i++)
					{
						Add(data.GetData()[i]);
					};
				};

				void AddUnique(T a)
				{
					bool exists = false;
					for(int i = 0; i < _Size; i++)
					{
						if((*(GetData(i))) == a)
						{
							exists = true;
							break;
						}
					}
					if(!exists)
					{
						Add(a);
					};
				};

				void Remove(int a)
				{
					T* tempArray = new T[_Size - 1];
					uint tempArrayIndex = 0;
					for(int i = 0; i < _Size; i++){
						if(i != a){
							tempArray[tempArrayIndex] = _DataArray[i];
							tempArrayIndex++;
						};
					};
					delete[] _DataArray;
					_DataArray = tempArray;
					_Size--;
					_NextAvailableIndex = _Size;
					_ActualSize = _Size;
				};

				void RemoveLast(){
					_DataArray[_Size - 1] = null;
					_Size--;
					_NextAvailableIndex--;
				};

				void RemoveMultiple(Array<uint> indices){
					T* tempArray = new T[_Size - indices];
					uint tempArrayIndex = 0;
					for(int i = 0; i < _Size; i++){
						if(!indices.Contains(i)){
							tempArray[tempArrayIndex] = _DataArray[i];
							tempArrayIndex++;
						}
					};
					delete[] _DataArray;
					_DataArray = tempArray;
					_Size -= indices.GetSize();
					_NextAvailableIndex = _Size;
					_ActualSize = _Size;
				};

				void Clear()
				{
					if(_ActualSize > 0)
					{
						try
						{
							delete[] _DataArray;
						}
						catch(...)
						{
							//v5Error error (5, "An Array failed to release it's data array upon it's destruction.");
							//error.Print();
						}
					};
					_Size = 0;
					_ActualSize = 0;
					_NextAvailableIndex = 0;
				};

				void Delete()
				{
					for(int i = 0; i < _Size; i++)
					{
						try
						{
							delete &(_DataArray[i]);
						}
						catch(...)
						{
							//try
							//{
							//	delete (void*)&_DataArray[i];
							//}
							//catch(...)
							//{
//								v5Error e(65535, "Array failed to delete the contents of it's data array.");
							//	e.Print();
							//};
						};
					};
				};

				Array<T> Clone()
				{
					Array<T> newArray ();
					for(int i = 0; i < _Size; i++)
					{
						newArray((*(GetData(i))));
					};
					return newArray;
				};

				void operator =(Array<T>& a)
				{
					Clear();
					
					_ResizeAmount = 5;
					_DataArray = new T[a.GetSize()];
					for(int i = 0; i < a.GetSize(); i++)
					{
						Add(*(a.GetData(i)));
					};
				};

				void operator =(v5CArrayData<T> a)
				{
					Clear();
					_ResizeAmount = 5;
					for(uint i = 0; i < a.GetLength(); i++)
					{
						Add(a.GetData()[i]);
					};
				};

				Reference<T> operator [](int a)
				{
					return GetData(a);
				};

				bool Contains(T a)
				{
					for(int i = 0; i < _Size; i++)
					{
						if(_DataArray[i] == a) return true;
					};
					return false;
				};

				T& GetReferenceData(int index)
				{
					return _DataArray[index];
				};
			};
		};
	};
};
#endif