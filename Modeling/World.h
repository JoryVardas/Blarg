//
#ifndef __WORLD_H__
#define __WORLD_H__

#include "v5Error.h"
//#include "Math.h"
//#include "Vector.h"
#include "Global_Variables.h"
#include "Mesh.h"
#include "Array.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{

			using namespace BrokenTechStudios::Nuke::Core;

			struct World
			{
				Array<Mesh> _Meshs;
				v5String _WorldFolder;

				World(World& w){
					//Load(w._WorldFolder);
				};
				World(){};
				World(v5String path, HWND hWnd){
					Load(path, hWnd);
				};

				~World(){
				//	_Meshs.Clear();
				};

				chained(World) AddMesh(v5String path){
					_Meshs.Add(Mesh(path.GetCString(), null));
					chainedReturn;
				};
				chained(World) AddMesh(Mesh& mesh){
					_Meshs.Add(mesh);
					chainedReturn;
				};
				/*chained(World) AddMesh(Mesh mesh){
					_Meshs.Add(mesh);
					chainedReturn;
				};*/
				Mesh& CreateMesh(){
					_Meshs.Add(Mesh());
					return _Meshs[_Meshs.GetSize() - 1].GetData();
				};

				int GetNumberOfMeshs(){
					return _Meshs.GetSize();
				};
				void Release(){
					_Meshs.Clear();
					_WorldFolder.Clear();
				};

				void operator =(World& w){
					_WorldFolder = w._WorldFolder;
					//Load(_WorldFolder);
				};

				void Save(HWND hWnd)
				{
					SettingsFile settings(_WorldFolder + "\\World.settings");
					if(settings.Exists())
					{
						for(int i = 0; i < _Meshs.GetSize(); i++)
						{
							if(settings.ContainsElement(_Meshs[i].GetData().GetName()))
							{
								_Meshs[i].GetData().Save(hWnd);
							}
							else
							{
								_Meshs[i] = _Meshs[i].GetData().SaveAs((_WorldFolder + "\\") + _Meshs[i].GetData().GetName(), hWnd);
								settings.AppendNewElement(_Meshs[i].GetData().GetName(), _WorldFolder + "\\" + _Meshs[i].GetData().GetName());
							};
						};
					}
					else
					{
						for(int i = 0; i < _Meshs.GetSize(); i++)
						{
							_Meshs[i] = _Meshs[i].GetData().SaveAs((_WorldFolder + "\\") + _Meshs[i].GetData().GetName(), hWnd);
							settings.AppendNewElement(_Meshs[i].GetData().GetName(), _WorldFolder + "\\" + _Meshs[i].GetData().GetName());
						};
					};
				};
				World* SaveAs(v5String newPath, HWND hWnd)
				{
					SettingsFile settings;
					settings.OpenNoLoad(newPath + "\\World.settings");
					uint testInt = 0;
					v5String temp = newPath;
					while(true)
					{
						if(settings.Exists())
						{
							temp = newPath + v5String::ToString(testInt);
							settings.Close();
							settings.OpenNoLoad(temp + "\\World.settings");
							testInt++;
						}
						else
						{
							v5String command = "mkdir ";
							command += '"';
							command += temp;
							command += '"';
							system(command.GetCString());
							command.Clear();
							break;
						};
					};
					for(int i = 0; i < _Meshs.GetSize(); i++)
					{
						v5String name = _Meshs.GetReferenceData(i).GetName();
						if(name.GetSize() <= 0 || name.GetSize() >= 3435973835)
						{
							name = "Unknown";
						};
						_Meshs[i].GetData().SaveAs((temp + "\\") + name + ".mesh", hWnd);
						settings.AppendNewElement(name, temp + "\\" + name + ".mesh");
					};
					settings.AppendNewElement("NumberMeshs", v5String::ToString((uint)_Meshs.GetSize()));
					//return &World(newPath);
					return null;
				};
				void Load(v5String path, HWND hWnd)
				{
					Release();
					_WorldFolder = path;
					SettingsFile settings(path + "\\World.settings");
					v5String nMeshsStr = settings.GetElementValue("NumberMeshs");
					uint numberOfMeshs = nMeshsStr.ToUINT();//stored on last line of file!
					for(int i = 0; i < numberOfMeshs; i++)
					{
						Mesh mesh = Mesh(settings.GetElementValue(i).GetCString(), hWnd);
						_Meshs.Add(mesh);
					};
				};
				void Clear()
				{
					Release();
				};
			};
		};
	};
};
#endif