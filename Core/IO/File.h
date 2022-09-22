//DONE

//events not fully implimented
#ifndef __FILE_H__
#define __FILE_H__

#include "Global_Variables.h"
#include "v5Error.h"
#include "Array.h"
#include "v5Object.h"
#include "StreamReader.h"
#include "StreamWriter.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			namespace IO
			{
				class File : public v5Object
				{
				protected:
					StreamReader _Reader;
					StreamWriter _Writer;
					char*	_FilePath;
					char*	_FileExtension;
					char*	_FileName;
					char*	_ContainingDirectory;
					bool	_FileType;
					bool _FileIsOpen;

				public:
					File() : v5Object(vptr(this))
					{
						_FilePath = null;
						_FileName = null;
						_FileExtension = null;
						_ContainingDirectory = null;
						_FileType = false;
						_FileIsOpen = false;
					};
					File(char* path) : v5Object(vptr(this))
					{
						_FilePath = path;
						_Writer.Open(path);
						_Reader.OpenNoCheck(path);
						_FileType = IsFile();
						_FileName = GetFileName();
						_FileExtension = GetExtension();
						_ContainingDirectory = GetContainingDirectory();
						_FileIsOpen = true;
					};
					~File()
					{
						_FilePath = null;
						_FileName = null;
						_FileExtension = null;
						_ContainingDirectory = null;
						_FileType = false;
						_FileIsOpen = false;
						_Reader.Close();
						_Writer.Close();
					};
	
					bool IsDirectory()
					{
						return ((bool)((GetFileAttributes(_FilePath)) & FILE_ATTRIBUTE_DIRECTORY));
					};
					bool IsFile()
					{
						return !((GetFileAttributes(_FilePath)) & FILE_ATTRIBUTE_DIRECTORY);
					};
					char* GetExtension()
					{
						string fullname = _FilePath;
						return (char*)(fullname.substr(fullname.find_last_of('.') + 1)).c_str();
					};
					char* GetFileName()
					{
						string fullname = _FilePath;
						size_t startPos = fullname.find_last_of('\\') + 1;
						return (char*)(fullname.substr(startPos, fullname.find_last_of('.') - startPos).c_str());
					};
					char* GetContainingDirectory()
					{
						string fullname = _FilePath;
						size_t length = fullname.find_last_of('\\');
						return (char*)(fullname.substr(0, length)).c_str();
					};
					char* GetContainingFolderName(){
						string fullname = GetContainingDirectory();
						size_t start = fullname.find_last_of('\\');
						return (char*)(fullname.substr(start + 1, fullname.length())).c_str();
					};
					char* GetFullPath()
					{
						return _FilePath;
					};

					//index = zero based index of the line
					char* GetLine(int index){
						return null;
					};
					//not implimented yet
					int GetNumberOfCharactersRead(){
						return null;
					};
					void Delete()
					{
						remove(_FilePath);
						Close();
					};
					
					void SaveAs(char* newPath){
						File f (newPath);
						CharArray buffer = f.Read();
						f.Write(buffer.GetData(), buffer.GetLength());
						f.Close();
					};
					void Move(char* newPath){
						MoveFile(_FilePath, newPath);
						Close();
						Open(newPath);
					};
					//needs different implimentation
					CharArray Read(){
						return _Reader.Read();
					};
					CharArray Read(int numberOfChars){
						return _Reader.Read(numberOfChars);
					};
					CharArray Read(int startIndex, int endIndex){
						return _Reader.Read(startIndex, endIndex);
					};
					void Write(v5CArrayData<char> buffer){
						_Writer.Write(buffer.GetData(), buffer.GetLength());
					};
					void Write(const char* buffer, uint length){
						_Writer.Write((char*)buffer, length);
					};
					 //does not save first
					void Open(char* path){
						_FilePath = path;
						_Writer.Open(path);
						_Reader.OpenNoCheck(path);
						_FileName = GetFileName();
						_FileExtension = GetExtension();
						_ContainingDirectory = GetContainingDirectory();
						_FileIsOpen = true;
					};
					void Close(){
						_Writer.Close();
						_Reader.Close();
					};
					int GetSize(){
						return _Reader.GetLength();
					};

					void operator =(File& f)
					{
						_FilePath = f._FilePath;
						_FileExtension = f._FileExtension;
						_FileName = f._FileName;
						_ContainingDirectory =f._ContainingDirectory;
						_FileType = f._FileType;
						Open(_FilePath);
					};


					void AppendToStart(v5CArrayData<char> buffer){
						CharArray temp = _Reader.Read();
						_Writer.Write(buffer.GetData(), buffer.GetLength(), 0);
						_Writer.Write(temp.GetData(), temp.GetLength(), buffer.GetLength());
					};
					//startIndex is zero based
					void Insert(v5CArrayData<char> buffer, int startIndex){
						CharArray temp = _Reader.Read(startIndex, _Reader.GetLength());
						_Writer.Write(buffer.GetData(), buffer.GetLength(), startIndex);
						_Writer.Write(temp.GetData(), temp.GetLength(), startIndex + buffer.GetLength());
					};
					void WriteLine(v5String& line)
					{
						line += __FILE_GET_LINE_DELIMINATING_CHARACTER__;
						_Writer.WriteToEnd(line.GetCString(), line.GetSize() + 1);
					};
					void RewriteLine(uint index, v5String line)
					{
						uint start = _Reader.GetStartOfLine(index);
						uint end = _Reader.GetStartOfLine(index + 1) - 2;
						CharArray endBuffer = _Reader.Read(end, -1);
						CharArray startBuffer = _Reader.Read(0, start - 1);
						Delete();
						_Writer.Write(startBuffer.GetData(), startBuffer.GetLength());
						_Writer.Write(line);
						_Writer.Write(endBuffer.GetData(), endBuffer.GetLength());
					};
					v5String ReadLine(uint index)
					{
						return _Reader.ReadLine(index);
					};
					uint GetNumberOfLines()
					{
						return _Reader.GetNumberOfLines();
					};
					bool Exists()
					{
						return _Reader.Exists();
					};
				};
			};
		};
	};
};
#endif