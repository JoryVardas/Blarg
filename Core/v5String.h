#ifndef __V5_STRING_H__
#define __V5_STRING_H__

#include "Global_Variables.h"
#include "ID_Manager.h"
#include "Reference.h"
#include "v5Object.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			struct v5String : public v5Object
			{
			private:
				char* _CharacterString;
				unsigned int _StringSize;
			public:
				v5String(v5String& s){
					_CharacterString = new char[s._StringSize];
					__COPY_ARRAY__<char>(_CharacterString, s._CharacterString, s._StringSize);
				_StringSize = s._StringSize;
				};
				v5String() : v5Object(this)
				{
					_CharacterString = null;
					_StringSize = 0;
				};
				v5String(char* cString, unsigned int cStringSize) : v5Object(this)
				{
					_CharacterString = new char[cStringSize];
					__COPY_ARRAY__<char>(_CharacterString, cString, cStringSize);
					_StringSize = cStringSize;
				};
				v5String(char* cString) : v5Object(this)
				{
					_StringSize = __GET_C_STRING_SIZE__(cString);
					_CharacterString = new char[_StringSize];
					__COPY_ARRAY__<char>(_CharacterString, cString, _StringSize);
				};
				~v5String()
				{
					__MEMORY_CHECK__
						if(_StringSize > 0 && _CharacterString != null){
						delete[] _CharacterString;
					};
					_StringSize = 0;
					_CharacterString = null;
					__MEMORY_CHECK__
				};

				char* GetCString()
				{
					return _CharacterString;
				};
				unsigned int GetSize()
				{
					return _StringSize - 1;
				};
				uint GetTrueLength(){
					return _StringSize;
				};
				void Clear()
				{
					if(_StringSize > 0){
						delete[] _CharacterString;
					};
					_StringSize = 0;
				};

				v5String operator +(v5String a){
					v5String ret(_CharacterString, _StringSize);
					ret += a;
					return ret;
				};
				v5String operator +(char* a){
					v5String ret(_CharacterString, _StringSize);
					ret += a;
					return ret;
				};
				void operator +=(v5String a){
					char* temp = new char[_StringSize + a._StringSize - 1];
					__COPY_ARRAY__<char>(temp, _CharacterString, _StringSize - 1);
					//gets a poiner to the position that would have been \0 from the first string.  look at theory for details.
					char* start = (char*)((uint)temp + _StringSize - 1);
					//copies the entire second string so that it does not have to add the \0 character later, as it is part of the second string.
					__COPY_ARRAY__<char>(start, a._CharacterString, a._StringSize);
					delete[] _CharacterString;
					_CharacterString = temp;
					_StringSize += a._StringSize - 1;
					//Dont forget to check for memory errors here as this is an unsafe function.
					__MEMORY_CHECK__
				};
				void operator +=(char* a){
					uint size = __GET_C_STRING_SIZE__(a);
					if(_StringSize > 0)
					{
						__MEMORY_CHECK__
						char* temp = new char[_StringSize + size - 1];
						__MEMORY_CHECK__
						__COPY_ARRAY__<char>(temp, _CharacterString, _StringSize -1);
						__MEMORY_CHECK__
						char* start = (char*)((uint)temp + _StringSize - 1);
						__MEMORY_CHECK__
						__COPY_ARRAY__<char>(start, a, size);
						__MEMORY_CHECK__
						delete[] _CharacterString;
						_CharacterString = temp;
						_StringSize += size - 1;
						__MEMORY_CHECK__
					}
					else
					{
						__MEMORY_CHECK__
						char* temp = new char[size];
						__MEMORY_CHECK__
						__COPY_ARRAY__<char>(temp, _CharacterString, size);
						__MEMORY_CHECK__
						_CharacterString = temp;
						_StringSize += size;
						__MEMORY_CHECK__
					};
				};
				void operator +=(char a){
					char* temp = new char[_StringSize + 1];
					__COPY_ARRAY__<char>(temp, _CharacterString, _StringSize -1);
					temp[_StringSize - 1] = a;
					temp[_StringSize] = '\0';
					delete[] _CharacterString;
					_CharacterString = temp;
					_StringSize += 1;
					__MEMORY_CHECK__
				};
				void operator =(v5String a){
					if(_StringSize > 0){
						delete[] _CharacterString;
						_StringSize = 0;
					};
					_CharacterString = new char[a._StringSize];
					__COPY_ARRAY__<char>(_CharacterString, a._CharacterString, a._StringSize);
					_StringSize = a._StringSize;
					__MEMORY_CHECK__
				};
				void operator =(char* a){
					if(_StringSize > 0){
						delete[] _CharacterString;
						_StringSize = 0;
					};
					uint size = __GET_C_STRING_SIZE__(a);
					_CharacterString = new char[size];
					__COPY_ARRAY__<char>(_CharacterString, a, size);
					_StringSize = size;
					__MEMORY_CHECK__
				};
				bool operator ==(v5String a){
					if(_StringSize != a._StringSize) return false;
					for(uint i = 0; i < _StringSize; i++){
						if(_CharacterString[i] != a._CharacterString[i]) return false;
					};
					return true;
				};
				bool operator ==(char* a){
					if(_StringSize != __GET_C_STRING_SIZE__(a)) return false;
					for(uint i = 0; i < _StringSize; i++){
						if(_CharacterString[i] != a[i]) return false;
					};
					return true;
				};
				bool operator !=(v5String a){
					if(_StringSize != a._StringSize) return true;
					for(uint i = 0; i < _StringSize; i++){
						if(_CharacterString[i] != a._CharacterString[i]) return true;
					};
					return false;
				};
				bool operator !=(char* a){
					if(_StringSize != __GET_C_STRING_SIZE__(a)) return true;
					for(uint i = 0; i < _StringSize; i++){
						if(_CharacterString[i] != a[i]) return true;
					};
					return false;
				};
				Reference<char> operator [](int index){
					return Reference<char>(&_CharacterString[index]);
				};

				bool ToBool()
				{
					if(_CharacterString == "true" || _CharacterString == "TRUE") return true;
					else return false;
				};

				uint ToUINT()
				{
					return (uint)atoi(_CharacterString);
				};

				float ToFloat()
				{
					return atof(_CharacterString);
				};

				static v5String ToString(bool b)
				{
					if(b) return v5String("true");
					else return v5String("false");
				};
				static v5String ToString(uint i)
				{
					char buffer[16];
					for(int i = 0; i < 16; i++)
					{
						buffer[i] = 'a';
					};
					_itoa_s(i, buffer, 10);
					Array<char> tempString;
					tempString.SetResizeAmount(1);
					for(int i = 0; i < 16; i++)
					{
						if(buffer[i] != 'a' && buffer[i] != '\0')
						{
							tempString.Add(buffer[i]);
						}
						else if(buffer[i] == '\0')
						{
							tempString.Add(buffer[i]);
							break;
						};
					};
					return v5String(tempString.GetData().GetData(), tempString.GetSize());
				};
				static v5String ToString(float i)
				{
					char buffer[512];
					sprintf_s(buffer, 512, "%f", i);
					Array<char> tempString;
					for(int i = 0; i < 512; i++)
					{
						tempString.Add(buffer[i]);
						if(buffer[i] == '\0')
						{
							break;
						};
					};
					return v5String(tempString.GetData().GetData(), tempString.GetSize());
				};
				/*static v5String ToString(long i)
				{
					char buffer[512];
					for(int i = 0; i < 512; i++)
					{
						buffer[i] = 'a';
					};
					_ltoa_s(i, buffer, 10);
					Array<char> tempString;
					tempString.SetResizeAmount(1);
					for(int i = 0; i < 512; i++)
					{
						if(buffer[i] == '\0')break;
						if(buffer[i] != 'a' && buffer[i] != '\0')
						{
							tempString.Add(buffer[i]);
						};
					};
					tempString.Add('\0');
					return v5String(tempString.GetData().GetData(), tempString.GetSize());
				};*/

				bool StartsWith(char* str)
				{
					uint size = __GET_C_STRING_SIZE__(str) - 1;
					for(int i = 0; i < size; i++)
					{
						if(_CharacterString[i] != str[i]) return false;
					};
					return true;
				};
				int GetFirstInstanceOf(char c)
				{
					for(int i = 0; i < _StringSize; i++)
					{
						if(_CharacterString[i] == c) return i;
					};
					return -1;
				};
				int GetFirstInstanceOf(char* str)
				{
					uint size = __GET_C_STRING_SIZE__(str) - 1;
					for(int i = 0; i < _StringSize - 1; i++)
					{
						for(int j = 0; j < size; j++)
						{
							if(_CharacterString[i + j] != str[j]) break;
							if(j == size - 1)
							{
								return i;
							};
						};
					};
					return -1;
				};
				v5String GetSubString(uint start, uint end)
				{
					if(start > _StringSize || end > _StringSize) return v5String();
					Array<char> buffer;
					for(int i = start; i < end + 1; i++)
					{
						buffer.Add(_CharacterString[i]);
					};
					buffer.Add('\0');
					v5CArrayData<char> ret = buffer.GetDataActual();
					return v5String(ret.GetData(), ret.GetLength());
				};
			};
		};
	};
};

#endif
