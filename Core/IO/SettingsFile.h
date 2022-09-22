#include "Global_Variables.h"
#include "File.h"

#ifndef __SETTINGS_FILE_H__
#define __SETTINGS_FILE_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace Core
		{
			namespace IO
			{
				struct SettingsFileElement
				{
					uint ID;
					v5String Name;

					SettingsFileElement(){};
					SettingsFileElement(uint id, v5String name)
					{
						ID = id;
						Name = name;
					};
					~SettingsFileElement(){};

					void operator =(SettingsFileElement& a)
					{
						ID = a.ID;
						Name = a.Name;
					};
				};
				class SettingsFile
				{
				private:
					File _Source;
					Array<SettingsFileElement> _Elements;
				public:
					SettingsFile(){
					};
					SettingsFile(File f){
						_Source = f;
						if(_Source.Exists())Load();
					};
					SettingsFile(char* path){
						_Source.Open(path);
						if(_Source.Exists())Load();
					};
					SettingsFile(v5String path){
						_Source.Open(path.GetCString());
						if(_Source.Exists())Load();
					};
					~SettingsFile(){
						_Source.Close();
						_Elements.Clear();
					};

					void Open(v5String path){
						_Source.Open(path.GetCString());
						if(_Source.Exists())Load();
					};
					void OpenNoLoad(v5String path){
						_Source.Open(path.GetCString());
					};
					void Close()
					{
						_Source.Close();
						_Elements.Clear();
					};

					void Load()
					{
						uint numberOfLines = _Source.GetNumberOfLines();
						for(int i = 0; i < numberOfLines; i++)
						{
							v5String line = _Source.ReadLine(i);
							if(line.StartsWith("<el "))
							{
								uint start = 4;
								uint end = line.GetFirstInstanceOf('>') - 1;
								v5String name = line.GetSubString(start, end);
								_Elements.Add(SettingsFileElement(i, name));
							};
						};
					};
					v5String GetElementValue(v5String name)
					{
						for(int i = 0; i < _Elements.GetSize(); i++)
						{
							if(_Elements[i]->Name == name)
							{
								v5String line = _Source.ReadLine(_Elements[i]->ID);
								uint start = line.GetFirstInstanceOf('>') + 1;
								uint end = line.GetFirstInstanceOf("</>") - 1;
								return line.GetSubString(start, end);
							};
						};
						return v5String("");
					};
					v5String GetElementValue(uint index)
					{
						v5String line = _Source.ReadLine(_Elements[index]->ID);
						uint start = line.GetFirstInstanceOf('>') + 1;
						uint end = line.GetFirstInstanceOf("</>") - 1;
						return line.GetSubString(start, end);
					};
					v5String GetChildElementValue(v5String parentName, uint childNumber)
					{
						for(int i = 0; i < _Elements.GetSize(); i++)
						{
							if(_Elements[i]->Name == parentName)
							{
								v5String line = _Source.ReadLine(_Elements[i]->ID + childNumber);
								if(line.StartsWith("<sub")){
									uint start = line.GetFirstInstanceOf('>') + 1;
									uint end = line.GetFirstInstanceOf("</>") - 1;
									return line.GetSubString(start, end);
								};
							};
						};
					};
					v5String GetChildElementValue(uint parentIndex, uint childNumber)
					{
						v5String line = _Source.ReadLine(_Elements[parentIndex]->ID + childNumber);
						if(line.StartsWith("<sub")){
							uint start = line.GetFirstInstanceOf('>');
							uint end = line.GetFirstInstanceOf("</>");
							return line.GetSubString(start, end);
						};
					};
					void SetElementValue(v5String name, v5String value)
					{
						for(int i = 0; i < _Elements.GetSize(); i++)
						{
							if(_Elements[i]->Name == name)
							{
								v5String line = "<el ";
								line += _Elements[i]->Name + ">";
								line += value + "</>";
								_Source.RewriteLine(_Elements[i]->ID, line);
							};
						};
					};
					void SetChildElementValue(v5String parentName, uint childNumber, v5String value)
					{
						for(int i = 0; i < _Elements.GetSize(); i++)
						{
							if(_Elements[i]->Name == parentName)
							{
								v5String line = "<sub>";
								line += value + "</>";
								_Source.RewriteLine(_Elements[i]->ID + childNumber, line);
							};
						};
					};
					void SetChildElementValue(uint parentIndex, uint childNumber, v5String value)
					{
						v5String line = "<sub>";
						line += value + "</>";
						_Source.RewriteLine(_Elements[parentIndex]->ID + childNumber, line);
					};
					void AppendNewElement(v5String name, v5String value)
					{
						v5String line = "<el ";
						line += name + ">";
						line += value + "</>";
						_Source.WriteLine(line);
					};
					void AppendNewChildElement(v5String value)
					{
						v5String line = "<sub>";
						line += value;
						line += "</>";
						_Source.WriteLine(line);
					};
					int ElementExists(v5String name)
					{
						for(int i = 0; i < _Elements.GetSize(); i++)
						{
							if(_Elements[i]->Name == name) return i;
						};
						return -1;
					};
					void Delete()
					{
						_Source.Delete();
					};
					bool Exists()
					{
						return _Source.Exists();
					};
					bool ContainsElement(v5String name)
					{
						for(int i = 0; i < _Elements.GetSize(); i++)
						{
							if(_Elements[i]->Name == name) return true;
						};
						return false;
					};
				};
			};
		};
	};
};

#endif