#include "Global_Variables.h"
#include "FileStreamReaderFileNonexistant.h"
#include "AttemptToCopyFileStream.h"
#include "v5String.h"

#ifndef __STREAM_READER_H__
#define __STREAM_READER_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			namespace IO
			{
				class StreamReader
				{
				private:
					v5String _Path;
					ios_base::openmode _Mode;
					Array<uint> _NewLineCharacterLocationMap;
					bool _NewLineCharacterMapExists;
				public:
					StreamReader(){};
					StreamReader(v5String path){
						_Path = path;
						_Mode = ios_base::in;
						if(!Exists()){
							FileStreamReaderFileNonexistant();
						};
						_NewLineCharacterMapExists = false;
					};
					StreamReader(v5String path, ios_base::openmode mode){
						_Path = path;
						_Mode = mode;
						if(!Exists()){
							FileStreamReaderFileNonexistant();
						};
						_NewLineCharacterMapExists = false;
					};
					StreamReader(char* path){
						_Path = path;
						_Mode = ios_base::in;
						if(!Exists()){
							FileStreamReaderFileNonexistant();
						};
						_NewLineCharacterMapExists = false;
					};
					StreamReader(char* path, ios_base::openmode mode){
						_Path = path;
						_Mode = mode;
						if(!Exists()){
							FileStreamReaderFileNonexistant();
						};
						_NewLineCharacterMapExists = false;
					};
					~StreamReader(){
						_Path.Clear();
						_NewLineCharacterLocationMap.Clear();
						_NewLineCharacterMapExists = false;
					};

					bool Exists(){
						ifstream reader (_Path.GetCString(), _Mode);
						bool exists = reader.is_open();
						reader.close();
						return exists;
					};

					long GetLength(){
						ifstream reader (_Path.GetCString(), _Mode);
						long length = 0;
						reader.seekg(ios::beg);
						while(true)
						{
							char buffer[1];
							reader.read(buffer, 1);
							if(reader.eof()) break;
							else length++;
						};
						reader.close();
						return length + 2;
					};

					CharArray Read(){
						ifstream reader (_Path.GetCString(), _Mode);
						char* buffer = new char[GetLength()];
						reader.seekg(reader.beg);
						reader.read(buffer, GetLength());
						reader.close();
						return CharArray(buffer, GetLength());
					};

					CharArray Read(uint number){
						ifstream reader (_Path.GetCString(), _Mode);
						char* buffer = new char[number + 1];
						reader.read(buffer, number);
						reader.close();
						buffer[number] = '\0';
						return CharArray(buffer, number + 1);
					};

					//includes start and end
					CharArray Read(uint start, uint end){
						ifstream reader (_Path.GetCString(), _Mode);
						if(end == -1)
						{
							reader.seekg(reader.end);
							end = reader.tellg();
						};
						char* buffer = new char[end - start + 2];
						reader.seekg(start - 1);
						reader.read(buffer, end - start + 1);
						reader.close();
						buffer[end - start + 1] = '\0';
						return CharArray(buffer, end - start + 2);
					};

					//zero based index
					v5String ReadLine(int lineIndex){
						__MEMORY_CHECK__
						ifstream reader (_Path.GetCString(), _Mode);
						
						__MEMORY_CHECK__
						if(_NewLineCharacterMapExists)
						{
						__MEMORY_CHECK__
							uint start = _NewLineCharacterLocationMap.GetReferenceData(lineIndex);
						__MEMORY_CHECK__
							uint end = _NewLineCharacterLocationMap.GetReferenceData(lineIndex + 1);
						__MEMORY_CHECK__
							if(lineIndex > 0){
								start += lineIndex + 1;
								end += lineIndex;
							};
						__MEMORY_CHECK__
							if(end < start) start = end;
							reader.seekg(start, ios::beg);
						__MEMORY_CHECK__
							char* buffer = new char[end - start + 1];
						__MEMORY_CHECK__
							reader.read(buffer, end - start);
						__MEMORY_CHECK__
							buffer[end - start] = '\0';
						__MEMORY_CHECK__
							reader.close();
							v5String ret = buffer;
						__MEMORY_CHECK__
							delete[] buffer;
						__MEMORY_CHECK__
							return ret;
						}
						else
						{
						__MEMORY_CHECK__
							int length = GetLength();
						__MEMORY_CHECK__
							_NewLineCharacterLocationMap.Add(0);
						__MEMORY_CHECK__
							reader.seekg(ios::beg);
						__MEMORY_CHECK__
							for(int i = 0; i < length; i++)
							{
						__MEMORY_CHECK__
								char buffer[1];
						__MEMORY_CHECK__
								reader.read(buffer, 1);
						__MEMORY_CHECK__
								if(reader.eof())
								{
									_NewLineCharacterLocationMap.Add(i);
						__MEMORY_CHECK__
									break;
								};
								if(buffer[0] == __FILE_GET_LINE_DELIMINATING_CHARACTER__)
								{
									_NewLineCharacterLocationMap.Add(i);
						__MEMORY_CHECK__
								};
						__MEMORY_CHECK__
							};
						__MEMORY_CHECK__
							reader.close();
						__MEMORY_CHECK__
							_NewLineCharacterMapExists = true;
							return ReadLine(lineIndex);
						};
					};

					uint GetNumberOfLines()
					{
						ifstream reader(_Path.GetCString(), _Mode);
						uint numberLines = 0;
						reader.seekg(reader.beg);
						while(true)
						{
							char buffer[1];
							reader.read(buffer, 1);
							if(buffer[0] == '\n') numberLines++;
							if(reader.eof()) break;
						};
						reader.close();
						return numberLines;
					};

					uint GetStartOfLine(int index)
					{
						if(index <= 0) return 0;
						ifstream reader(_Path.GetCString(), _Mode);
						uint numberLines = 0;
						reader.seekg(reader.end);
						uint length = reader.tellg();
						if(index >= GetNumberOfLines())
						{
							reader.close();
							return length;
						};
						reader.seekg(reader.beg);
						uint bufferNumber = 0;
						char buffer[255];
						while(true)
						{
							reader.seekg(bufferNumber * 255);
							reader.read(buffer, 255);
							for(int i = 0; i < 255 ; i++)
							{
								if(buffer[i] == __FILE_GET_LINE_DELIMINATING_CHARACTER__) numberLines++;
								if(numberLines == index)
								{
									reader.close();
									return (bufferNumber * 255) + i + 1;
								};
							};
						};
					};

					//need more read functions??

					void OpenNoCheck(char* path){
						_Path = path;
						_Mode = ios_base::in;
						_NewLineCharacterMapExists = false;
					};

					void Close(){
						_Path.Clear();
					};

					void operator =(StreamReader& reader){
						AttemptToCopyFileStream();
					};
					void operator =(StreamReader* reader){
						AttemptToCopyFileStream();
					};
				};
			};
		};
	};
};

#endif