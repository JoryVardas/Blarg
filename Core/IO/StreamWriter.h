#include "Global_Variables.h"
#include "AttemptToCopyFileStream.h"
#include "v5String.h"

#ifndef __STREAM_WRITER_H__
#define __STREAM_WRITER_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			namespace IO
			{
				class StreamWriter
				{
				private:
					v5String _Path;
					ios_base::openmode _Mode;
				public:
					StreamWriter(){};
					StreamWriter(v5String path){
						_Path = path;
						_Mode = ios_base::out;
					};
					StreamWriter(v5String path, ios_base::openmode mode){
						_Mode = mode;
						_Path = path;
					};
					StreamWriter(char* path){
						_Mode = ios_base::out;
						_Path = path;
					};
					StreamWriter(char* path, ios_base::openmode mode){
						_Mode = mode;
						_Path = path;
					};
					~StreamWriter(){
						_Path.Clear();
					};

					//checks to see if the opened file stream containes any data, if it does not it assumes that the file does not exist.
					bool Exists(){
						ofstream writer(_Path.GetCString(), _Mode);
						long pos = (writer.seekp(writer.end)).tellp();
						writer.close();
						return pos > 0;
					};

					v5String GetPath(){
						return _Path;
					};

					void Write(v5String text){
						ofstream writer(_Path.GetCString(), _Mode);
						writer.write(text.GetCString(), text.GetTrueLength());
						writer.flush();
						writer.close();
					};

					void Write(v5String text, long position){
						ofstream writer(_Path.GetCString(), _Mode);
						writer.seekp(position);
						writer.write(text.GetCString(), text.GetTrueLength());
						writer.flush();
						writer.close();
					};

					void Write(v5String text, ios_base::streampos position){
						ofstream writer(_Path.GetCString(), _Mode);
						writer.seekp(position);
						writer.write(text.GetCString(), text.GetTrueLength());
						writer.flush();
						writer.close();
					};

					void Write(const char* text, int size){
						ofstream writer(_Path.GetCString(), _Mode);
						writer.seekp(writer.end);
						writer.write(text, size - 1);
						writer.flush();
						writer.close();
					};

					void WriteToEnd(char* text, int size)
					{
						ofstream writer(_Path.GetCString(), ios::app);
						writer.seekp(writer.end);
						writer.write(text, size - 1);
						writer.flush();
						writer.close();
					};
					
					void Write(char* text, int size, long position){
						ofstream writer(_Path.GetCString(), _Mode);
						writer.seekp(position);
						writer.write(text, size - 1);
						writer.flush();
						writer.close();
					};
					void Write(char* text, int size,  ios_base::streampos position){
						ofstream writer(_Path.GetCString(), _Mode);
						writer.seekp(position);
						writer.write(text, size - 1);
						writer.flush();
						writer.close();
					};

					void Close(){
						_Path.Clear();
					};
					
					void Open(v5String path){
						_Path = path;
						_Mode = ios_base::out;
					};

					void Open(char* path){
						_Path = path;
						_Mode = ios_base::out;
					};

					void Open(v5String path, ios_base::openmode mode){
						_Path = path;
						_Mode = mode;
					};

					void Open(char* path, ios_base::openmode mode){
						_Path = path;
						_Mode = mode;
					};
					
					void operator =(StreamWriter& writer){
						AttemptToCopyFileStream();
					};
					void operator =(StreamWriter* writer){
						AttemptToCopyFileStream();
					};
				};
			};
		};
	};
};

#endif