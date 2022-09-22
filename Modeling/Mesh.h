//
#ifndef __MESH_H__
#define __MESH_H__

#include "Ray.h"
#include "Vector.h"
#include "Face.h"
#include "TriangleFace.h"
#include "v5Math.h"
#include "File.h"
#include "v5Error.h"
#include "Global_Variables.h"
#include "ID_Manager.h"
#include "Texture.h"
#include "IndexTriangle.h"
#include "ReplaceEveryInstanceOf.h"
#include "v5String.h"
#include "SettingsFile.h"

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			using namespace Core;

			class Mesh : public v5Object
			{
			private:
				Array<Vertex> _VertexArray;
				Array<WORD> _IndexArray;
				bool _Visable;
				bool _TriangleFaces;
				//Texture _Texture;
			public:
				//Array<Vertex> _VertexRendererVertexArray;
				//Array<WORD> _VertexRendererIndexArray;
				//bool _VertexRendererUpdate;
				float _X, _Y, _Z;

				v5String _MeshFileLocation;
				v5String _Name;

				Mesh(Mesh& a){
					_TriangleFaces = a._TriangleFaces;
					_Visable = a._Visable;
					_VertexArray = a._VertexArray;
					_IndexArray = a._IndexArray;
					_Name = a._Name;
					_X = a._X;
					_Y = a._Y;
					_Z = a._Z;
					//_VertexRendererUpdate = true;
				};
				Mesh() : v5Object(this, 1){
					_TriangleFaces = false;
					_Visable = false;
					_MeshFileLocation = "";
					_X = _Y = _Z = 0;
					_VertexArray.Clear();
					_IndexArray.Clear();
					//_VertexRendererUpdate = true;
					//_Name = __INT_TO_STRING__(_ID);
				};
				Mesh(char* meshLocation, HWND hWnd) : v5Object(this, 1){
					_MeshFileLocation = meshLocation;
					Load(hWnd);
					//_VertexRendererUpdate = true;
				};
				~Mesh(){
					_VertexArray.Clear();
					_IndexArray.Clear();
				};

	
				//for rendering only!
				//any changes to the arrays returned by GetVertexArrayPtr and GetIndexArrayPtr may or may not affect the model's vertex and index arrays.
				//it is therefor advisanble to not try to modify the contents of these arrays.
				//To modify the contents of the Mesh's vertex and index arrays use GetVertexArrayDirect and GetIndexArrayDirect.
				v5CArrayData<Vertex> GetVertexArrayPtr(){
					return _VertexArray.GetDataActual();
				};
				v5CArrayData<WORD> GetIndexArrayPtr(){
					return _IndexArray.GetDataActual();
				};
				v5CArrayData<Vertex> GetVertexArrayDirect()
				{
					return _VertexArray.GetData();
				};
				v5CArrayData<WORD> GetIndexArrayDirect(){
					return _IndexArray.GetData();
				};
				uint GetNumberOfVertices(){
					return _VertexArray.GetSize();
				};
				uint GetNumberOfIndices(){
					return _IndexArray.GetSize();
				};
				//Texture* GetTexture()
				//{
				//	return &_Texture;
				//};
				bool IsVisable(){
					return _Visable;
				};
				chained(Mesh) SetVisable(bool visable){
					_Visable = visable;
					chainedReturn;
				};
				chained(Mesh) SetName(v5String name){
					_Name = name;
					chainedReturn;
				};
				v5String GetName(){
					return _Name;
				};

				//zero based!
				Face GetNthFace(int n){
					return Face(_VertexArray[_IndexArray[n * 6].GetData()].GetPtr(), _VertexArray[_IndexArray[(n * 6) + 1].GetData()].GetPtr(), _VertexArray[_IndexArray[(n * 6) + 2].GetData()].GetPtr(), _VertexArray[_IndexArray[(n * 6) + 3].GetData()].GetPtr());
				};
				TriangleFace GetNthTriangleFace(int n)
				{
					return TriangleFace(_VertexArray[_IndexArray[n * 3].GetData()].GetPtr(), _VertexArray[_IndexArray[(n * 3) + 1].GetData()].GetPtr(), _VertexArray[_IndexArray[(n * 3) + 2].GetData()].GetPtr());
				};
	
				void operator =(Mesh& a){
					_Visable = a._Visable;
					_VertexArray = a._VertexArray;
					_IndexArray = a._IndexArray;
					_Name = a._Name;
					_X = a._X;
					_Y = a._Y;
					_Z = a._Z;
					_TriangleFaces = a._TriangleFaces;
				};
				void AddVertexQuad(Vertex v, Vertex v1, Vertex v2, Vertex v3){
					WORD index = _VertexArray.GetSize();
					_IndexArray.Add(index + 1);
					_IndexArray.Add(index);
					_IndexArray.Add(index + 2);
					_IndexArray.Add(index + 1);
					_IndexArray.Add(index + 2);
					_IndexArray.Add(index + 3);
					_VertexArray.Add(v);
					_VertexArray.Add(v1);
					_VertexArray.Add(v2);
					_VertexArray.Add(v3);
				};
				void AddVertices(Vertex v, Vertex v2, Vertex v3, Vertex v4){
					_VertexArray.Add(v);
					_VertexArray.Add(v2);
					_VertexArray.Add(v3);
					_VertexArray.Add(v4);
				};
				void AddVertices(Vertex v, Vertex v2, Vertex v3){
					_VertexArray.Add(v);
					_VertexArray.Add(v2);
					_VertexArray.Add(v3);
				};
				void AddVertex(Vertex v){
					_VertexArray.Add(v);
				};
				void AddVertexTri(Vertex v, Vertex v1, Vertex v2)
				{
					_IndexArray.Add(_VertexArray.GetSize());
					_IndexArray.Add(_VertexArray.GetSize()+1);
					_IndexArray.Add(_VertexArray.GetSize()+2);
					_VertexArray.Add(v);
					_VertexArray.Add(v1);
					_VertexArray.Add(v2);
				};
				void AddIndexTriangle(WORD i, WORD i2, WORD i3){
					_IndexArray.Add(i);
					_IndexArray.Add(i2);
					_IndexArray.Add(i3);
				};
			/*	void AddVertexTriangleWithTwoExisting(Vertex* v, WORD i, WORD i2){
					_VertexArray.Add(*v);
					_IndexArray.Add(i);
					_IndexArray.Add(i2);
					_IndexArray.Add(_VertexArray.GetSize() - 1);
				};*/
				void SetVertexArray(v5CArrayData<Vertex> a){
					_VertexArray = a;
				};
				void SetIndexArray(v5CArrayData<WORD> a){
					_IndexArray = a;
				};
				unsigned int GetNumberOfFaces(){
					//for every face there are six indices...
					if (_TriangleFaces)
					{
						return _IndexArray.GetSize() / 3;
					};
					return _IndexArray.GetSize() / 6;
				};
				void Clear(){
					if(_VertexArray.GetSize() > 0)_VertexArray.Clear();
					if(_IndexArray.GetSize() > 0) _IndexArray.Clear();
				};
				void AddIndexQuad(WORD i, WORD i1, WORD i2, WORD i3)
				{
					_IndexArray.Add(i1);
					_IndexArray.Add(i);
					_IndexArray.Add(i2);
					_IndexArray.Add(i3);
					_IndexArray.Add(i1);
					_IndexArray.Add(i2);
				};

				void Load(HWND hWnd)
				{
					SettingsFile source(_MeshFileLocation);
					if(hWnd != null){
					v5String update = "LOADING! Mesh: ";
					update += _Name;
					SetWindowText(hWnd, update.GetCString());};
					_Name = source.GetElementValue("Name");
					_Visable = source.GetElementValue("Visable").ToBool();
					_TriangleFaces = source.GetElementValue("TriangleFaces").ToBool();
					_X = source.GetChildElementValue("Position", 1).ToFloat();
					_Y = source.GetChildElementValue("Position", 2).ToFloat();
					_Z = source.GetChildElementValue("Position", 3).ToFloat();
					// line 3 should be the texture file path;
					uint numberVerts = source.GetElementValue("NumberVerts").ToUINT();
					uint numberInds = source.GetElementValue("NumberInds").ToUINT();
					for(int i = 0; i < numberVerts; i++)
					{
						if((i % 20) == 0)
						{
					if(hWnd != null){
							v5String update = "LOADING! Mesh: ";
							update += _Name;
							update += ", VertexArray: ";
							update += v5String::ToString((uint)i);
							update += " / ";
							update += v5String::ToString((uint)_VertexArray.GetSize());
							SetWindowText(hWnd, update.GetCString());};
						};
						float x = source.GetChildElementValue("VertexArray", (i * 10) + 1).ToFloat();
						float y = source.GetChildElementValue("VertexArray", (i * 10) + 2).ToFloat();
						float z = source.GetChildElementValue("VertexArray", (i * 10) + 3).ToFloat();
						float u = source.GetChildElementValue("VertexArray", (i * 10) + 4).ToFloat();
						float v = source.GetChildElementValue("VertexArray", (i * 10) + 5).ToFloat();
						float r = source.GetChildElementValue("VertexArray", (i * 10) + 6).ToFloat();
						float g = source.GetChildElementValue("VertexArray", (i * 10) + 7).ToFloat();
						float b = source.GetChildElementValue("VertexArray", (i * 10) + 8).ToFloat();
						float a = source.GetChildElementValue("VertexArray", (i * 10) + 9).ToFloat();
						float flag = source.GetChildElementValue("VertexArray", (i * 10) + 10).ToFloat();
						Vertex vert = {x, y, z, u, v, D3DXCOLOR(r, g, b, a), flag};
						_VertexArray.Add(vert);
					};
					for(int i = 0; i < numberInds; i++)
					{
						if((i % 20) == 0)
						{
					if(hWnd != null){
							v5String update = "LOADING! Mesh: ";
							update += _Name;
							update += ", IndexArray: ";
							update += v5String::ToString((uint)i);
							update += " / ";
							update += v5String::ToString((uint)_IndexArray.GetSize());
							SetWindowText(hWnd, update.GetCString());};
						};
						uint ind = source.GetChildElementValue("IndexArray", i + 1).ToUINT();
						_IndexArray.Add(ind);
					};
				};
				void Save(HWND hWnd)
				{
					SettingsFile dest(_MeshFileLocation);
					dest.Delete();
					if(hWnd != null){
					v5String update = "Nuke - 3D Modeling :: SAVING! Mesh: ";
					update += _Name;
					SetWindowText(hWnd, update.GetCString());};
					dest.AppendNewElement("Name", _Name);
					dest.AppendNewElement("Visable", v5String::ToString(_Visable));
					dest.AppendNewElement("TriangleFaces", v5String::ToString(_TriangleFaces));
					dest.AppendNewElement("Position", "");
					dest.AppendNewChildElement(v5String::ToString(_X));
					dest.AppendNewChildElement(v5String::ToString(_Y));
					dest.AppendNewChildElement(v5String::ToString(_Z));
					dest.AppendNewElement("NumberVerts", v5String::ToString((uint)_VertexArray.GetSize()));
					dest.AppendNewElement("NumberInds", v5String::ToString((uint)_IndexArray.GetSize()));
					dest.AppendNewElement("VertexArray", "");
					for(int i = 0; i < _VertexArray.GetSize(); i++)
					{
						if((i % 20) == 0)
						{
					if(hWnd != null){
							v5String update = "Nuke - 3D Modeling :: SAVING! Mesh: ";
							update += _Name;
							update += ", VertexArray: ";
							update += v5String::ToString((uint)i);
							update += " / ";
							update += v5String::ToString((uint)_VertexArray.GetSize());
							SetWindowText(hWnd, update.GetCString());};
						};
						Vertex* vert = _VertexArray.GetData(i);
						dest.AppendNewChildElement(v5String::ToString(vert->X));
						dest.AppendNewChildElement(v5String::ToString(vert->Y));
						dest.AppendNewChildElement(v5String::ToString(vert->Z));
						dest.AppendNewChildElement(v5String::ToString(vert->U));
						dest.AppendNewChildElement(v5String::ToString(vert->V));
						dest.AppendNewChildElement(v5String::ToString(vert->Color.r));
						dest.AppendNewChildElement(v5String::ToString(vert->Color.g));
						dest.AppendNewChildElement(v5String::ToString(vert->Color.b));
						dest.AppendNewChildElement(v5String::ToString(vert->Color.a));
						dest.AppendNewChildElement(v5String::ToString(vert->Selected));
					};
					dest.AppendNewElement("IndexArray", "");
					for(int i = 0; i < _IndexArray.GetSize(); i++)
					{
						if((i % 20) == 0)
						{
					if(hWnd != null){
							v5String update = "Nuke - 3D Modeling :: SAVING! Mesh: ";
							update += _Name;
							update += ", IndexArray: ";
							update += v5String::ToString((uint)i);
							update += " / ";
							update += v5String::ToString((uint)_IndexArray.GetSize());
							SetWindowText(hWnd, update.GetCString());};
						};
						dest.AppendNewChildElement(v5String::ToString((uint)_IndexArray[i].GetData()));
					};
				};
				Mesh* SaveAs(v5String& newPath, HWND hWnd)
				{
					SettingsFile dest(newPath);
					if(hWnd != null){
					v5String update = "SAVING! Mesh: ";
					update += _Name;
					SetWindowText(hWnd, update.GetCString());};
					dest.AppendNewElement("Name", _Name);
					dest.AppendNewElement("Visable", v5String::ToString(_Visable));
					dest.AppendNewElement("TriangleFaces", v5String::ToString(_TriangleFaces));
					dest.AppendNewElement("Position", "");
					dest.AppendNewChildElement(v5String::ToString(_X));
					dest.AppendNewChildElement(v5String::ToString(_Y));
					dest.AppendNewChildElement(v5String::ToString(_Z));
					dest.AppendNewElement("NumberVerts", v5String::ToString((uint)_VertexArray.GetSize()));
					dest.AppendNewElement("NumberInds", v5String::ToString((uint)_IndexArray.GetSize()));
					dest.AppendNewElement("VertexArray", "");
					for(int i = 0; i < _VertexArray.GetSize(); i++)
					{
						if((i % 20) == 0)
						{
					if(hWnd != null){
							v5String update = "SAVING! Mesh: ";
							update += _Name;
							update += ", VertexArray: ";
							update += v5String::ToString((uint)i);
							update += " / ";
							update += v5String::ToString((uint)_VertexArray.GetSize());
							SetWindowText(hWnd, update.GetCString());};
						};
						Vertex vert = _VertexArray[i].GetData();
						dest.AppendNewChildElement(v5String::ToString(vert.X));
						dest.AppendNewChildElement(v5String::ToString(vert.Y));
						dest.AppendNewChildElement(v5String::ToString(vert.Z));
						dest.AppendNewChildElement(v5String::ToString(vert.U));
						dest.AppendNewChildElement(v5String::ToString(vert.V));
						dest.AppendNewChildElement(v5String::ToString(vert.Color.r));
						dest.AppendNewChildElement(v5String::ToString(vert.Color.g));
						dest.AppendNewChildElement(v5String::ToString(vert.Color.b));
						dest.AppendNewChildElement(v5String::ToString(vert.Color.a));
						dest.AppendNewChildElement(v5String::ToString(vert.Selected));
					};
					dest.AppendNewElement("IndexArray", "");
					for(int i = 0; i < _IndexArray.GetSize(); i++)
					{
						if((i % 20) == 0)
						{
					if(hWnd != null){
							v5String update = "SAVING! Mesh: ";
							update += _Name;
							update += ", IndexArray: ";
							update += v5String::ToString((uint)i);
							update += " / ";
							update += v5String::ToString((uint)_IndexArray.GetSize());
							SetWindowText(hWnd, update.GetCString());};
						};
						dest.AppendNewChildElement(v5String::ToString((uint)_IndexArray[i].GetData()));
					};
					//return &Mesh(newPath.GetCString());
					return null;
				};
				Vertex* GetVertex(int index)
				{
					return _VertexArray.GetData(index);
				};
				bool UsesTriangleFaces()
				{
					return _TriangleFaces;
				};
				void SetUsesTriangleFaces(bool v)
				{
					_TriangleFaces = v;
				};
			};
		};
	};
};
#endif