#include "Global_Variables.h"
#include "Vertex.h"

#ifndef __EDGE_DATA_H__
#define __EDGE_DATA_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace _3DModeling
		{
			struct Temp_Edge_Data
			{
				Vertex* _Vert1;
				Vertex* _Vert2;
				float _ZAtPoint;

				Temp_Edge_Data(Temp_Edge_Data& data){
					_Vert1 = data._Vert1;
					_Vert2 = data._Vert2;
					_ZAtPoint = data._ZAtPoint;
				};
				Temp_Edge_Data()
				{
					_Vert1 = _Vert2 = null;
					_ZAtPoint = null;
				};
				Temp_Edge_Data(Vertex* v1, Vertex* v2, float zAtPoint)
				{
					_Vert1 = v1;
					_Vert2 = v2;
					_ZAtPoint = zAtPoint;
				};
				~Temp_Edge_Data()
				{
					_Vert1 = _Vert2 = null;
					_ZAtPoint = null;
				};

				Vertex* GetVertex1()
				{
					return _Vert1;
				};
				Vertex* GetVertex2()
				{
					return _Vert2;
				};
				float GetZAtPoint()
				{
					return _ZAtPoint;
				};
				void SetVertex1(Vertex* v)
				{
					_Vert1 = v;
				};
				void SetVertex2(Vertex* v)
				{
					_Vert2 = v;
				};
				void SetZAtPoint(float zAtPoint)
				{
					_ZAtPoint = zAtPoint;
				};

				void operator =(Temp_Edge_Data& ted)
				{
					_Vert1 = ted._Vert1;
					_Vert2 = ted._Vert2;
					_ZAtPoint = ted._ZAtPoint;
				};

				bool operator ==(Temp_Edge_Data& e)
				{
					return (_ZAtPoint == e._ZAtPoint);
				};
			};

			struct Edge_Data
			{
				Vertex* _Vert1;
				Vertex* _Vert2;
				void* _ContainingMesh;

				Edge_Data(Edge_Data& data){
					_Vert1 = data._Vert1;
					_Vert2 = data._Vert2;
					_ContainingMesh = data._ContainingMesh;
				};
				Edge_Data()
				{
					_ContainingMesh = _Vert1 = _Vert2 = null;
				};
				Edge_Data(Vertex* v1, Vertex* v2, void* containingMesh)
				{
					_Vert1 = v1;
					_Vert2 = v2;
					_ContainingMesh = containingMesh;
				};
				Edge_Data(Temp_Edge_Data ted, void* containingMesh)
				{
					_Vert1 = ted.GetVertex1();
					_Vert2 = ted.GetVertex2();
					_ContainingMesh = containingMesh;
				};
				~Edge_Data()
				{
					_ContainingMesh = _Vert1 = _Vert2 = null;
				};

				Vertex* GetVertex1()
				{
					return _Vert1;
				};
				Vertex* GetVertex2()
				{
					return _Vert2;
				};
				void* GetContainingMesh()
				{
					return _ContainingMesh;
				};
				void SetVertex1(Vertex* v)
				{
					_Vert1 = v;
				};
				void SetVertex2(Vertex* v)
				{
					_Vert2 = v;
				};

				void operator =(Edge_Data& ed)
				{
					_Vert1 = ed._Vert1;
					_Vert2 = ed._Vert2;
					_ContainingMesh = ed._ContainingMesh;
				};
			};
		};
	};
};
#endif