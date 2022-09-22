#ifndef __REFERENCE_H__
#define __REFERENCE_H__

#include "Global_Variables.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			template <typename T>
			class Reference
			{
			public:
				T* _Ptr;

				Reference<T>(Reference<T>& ref){
					_Ptr = ref._Ptr;
				};
				Reference<T>()
				{
					_Ptr = null;
				};

				Reference<T>(T* ptr)
				{
					_Ptr = ptr;
				};
				
				~Reference<T>()
				{
					_Ptr = null;
				};

				void SetPtr(T* ptr)
				{
					_Ptr = ptr;
				};

				T GetData()
				{
					return *_Ptr;
				};
				T* GetPtr()
				{
					return _Ptr;
				};

				void operator =(T data)
				{
					*_Ptr = data;
				};

				void operator =(T* ptr)
				{
					*_Ptr = *ptr;
				};

				void operator =(void* prt)
				{
					_Ptr = (T*)ptr;
				};
				
				bool operator ==(Reference<T> ref)
				{
					return (*_Ptr == *(ref._Ptr));
				};

				bool operator ==(T a)
				{
					return (*_Ptr == a);
				};

				bool operator !=(Reference<T> ref)
				{
					return (*_Ptr != *(ref._Ptr));
				};

				bool operator !=(T a)
				{
					return (*_Ptr != a);
				};

				T* operator ->()
				{
					return _Ptr;
				};

				T operator *()
				{
					return *_Ptr;
				};
			};

			class Void_Reference
			{
			public:
				void* _Ptr;

				Void_Reference(Void_Reference& r){
					_Ptr = r._Ptr;
				};
				Void_Reference()
				{
					_Ptr = null;
				};

				Void_Reference(void* ptr)
				{
					_Ptr = ptr;
				};
				
				~Void_Reference()
				{
					_Ptr = null;
				};

				void SetPtr(void* ptr)
				{
					_Ptr = ptr;
				};

				void* GetData()
				{
					return _Ptr;
				};

				template <typename T>
				void operator =(T data)
				{
					*(T*)_Ptr = data;
				};

				void operator =(void* ptr)
				{
					_Ptr = ptr;
				};
			};
		};
	};
};
#endif