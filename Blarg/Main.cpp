#include "Global_Variables.h"
#include "Window.h"
//#include "Vertex_Translate.h"
//#include "Vertex_Rotate.h"
//#include "Edge_Rotate.h"
//#include "Edge_Scale.h"
//#include "Edge_Translate.h"
//#include "Vertex_Select.h"
//#include "Edge_Select.h"
#include "v5String.h"
//#include "Vertex_Select.h"
//#include "Edge_Select.h"
//#include "Model_Translate.h"
#include "Create_Cube.h"
#include "Create_Sphere.h"
#include "Create_Plane.h"
#include "World.h"
//#include "StreamReader.h"
//#include "StreamWriter.h"
#include "Model_Rotate.h"
#include "Model_Translate.h"
#include "Model_Scale.h"
//#include "Face.h"
//#include "Face_Select.h"
#include "v5RenderState.h"
#include "WireframeRenderer.h"
#include "SolidRenderer.h"
#include "Create_Torus.h"
#include "Conversions.h"
#include "Face_Select.h"
#include "VertexRenderer.h"
#include "Vertex_Select.h"
#include "Edge_Split.h"
#include "Fuse_Vertices.h"

	using namespace BrokenTechStudios::Nuke::Core;
	using namespace BrokenTechStudios::Nuke::Core::IO;
	using namespace BrokenTechStudios::Nuke::UI;
	using namespace BrokenTechStudios::Nuke::_3DModeling::Tools;
	using namespace BrokenTechStudios::Nuke::_3DModeling;
	using namespace BrokenTechStudios::Nuke::Rendering;

	//transformation setting. 0 = translate, 1 = rotate, 2 = scale, 3 = none
	uint _TransformationSetting = 3;
	bool _CreatingNewObject = false;
	bool _CreationSetting = false;
	// 0 = world, 1 = model, 2 = face, 3 = vertex
	uint _SelectionType = 0;

	struct SelectionData
	{
		uint meshIndex;
		Vertex* vertex;
	};

	Array<SelectionData> _SelectedData;

	World _World;
	v5String _WorldFolder = "C:\\Users\\Joshua\\Documents\\PROJECTS\\TeamProjects\\Worlds\\";
	bool _Saving = false;
	bool _Loading = false;
	Window* _SaveLoadWindowPtr = null;
	Window* _MainWindowPtr = null;
	HWND _SaveLoadTextBoxHandlePtr;
	HWND _SaveButtonHandlePtr;
	HWND _LoadButtonHandlePtr;
	bool _SavingDone = false;
	bool _LoadingDone = false;

	void ClearSelectedData()
	{
		if(_SelectionType == 1)
		{
			for(int a = 0; a < _SelectedData.GetSize(); a++)
			{
				uint index = _SelectedData[a]->meshIndex;
				uint number = _World._Meshs[index]->GetNumberOfVertices();
				for(int i = 0; i < number; i++)
				{
					_World._Meshs[index]->GetVertex(i)->Color = __WIREFRAME_VERTEX_DEFAULT_COLOR__;
				};
				//_World._Meshs[index]->_VertexRendererUpdate = true;
			};
			_SelectedData.Clear();
		}
		else if(_SelectionType > 1)
		{
			__MEMORY_CHECK__
			for(int i = 0; i < _SelectedData.GetSize(); i++)
			{
				_SelectedData[i]->vertex->Color = __WIREFRAME_VERTEX_DEFAULT_COLOR__;
				//_World._Meshs[_SelectedData[i]->meshIndex]->_VertexRendererUpdate = true;
			};
			__MEMORY_CHECK__
			_SelectedData.Clear();
			__MEMORY_CHECK__
		};
	};

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
			case WM_DESTROY:
			{
				__IS_EXITING__ = true;
				PostQuitMessage(0);
				return 0;
				break;
			};
			
			//KEYS MUST BE PLACED WITH THE MAIN WINDOWS MESSAGE HANDLER, OTHERWISE THEY DO NOT GET FIRED!
			//Keys
			case WM_KEYDOWN:
				{
					switch(wParam)
					{
					case VK_BACK:
						{
							_TransformationSetting = 3;
							_CreationSetting = false;
							break;
						};
					case VK_SPACE:
					{
							ClearSelectedData();
							break;
						};
					case 0x52:
						{
							_TransformationSetting = 1;
							break;
						};
					case 0x53:
						{
							if(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_SHIFT))
							{
								if(!_Saving)
								{
									_Saving = true;
									SetWindowText(hWnd, "Nuke - 3D Modeling :: SAVING!");
									if(_SaveLoadWindowPtr != null)_SaveLoadWindowPtr->Show();
									ShowWindow(_LoadButtonHandlePtr, SW_HIDE);
									ShowWindow(_SaveButtonHandlePtr, SW_SHOW);
								};
							}
							else if(GetAsyncKeyState(VK_CONTROL))
							{
								if(!_Saving)
								{
									_Saving = true;
									SetWindowText(hWnd, "Nuke - 3D Modeling :: SAVING!");
									_World.Save(_MainWindowPtr->GetHandle());
									_Saving = false;
									_SavingDone = true;
								};
							}
							else
							{
								_TransformationSetting = 2;
							};
							break;
						};
					case 0x54:
						{
							_TransformationSetting = 0;
							break;
						};
					case VK_DOWN:
						{
							if(_SelectionType == 0)
							{
								if(_TransformationSetting == 1){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Rotate(_World._Meshs[i].GetPtr(), -0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Translate(_World._Meshs[i].GetPtr(), 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Scale(_World._Meshs[i].GetPtr(), 1, 0.99, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 1)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Rotate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), -0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Translate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Scale(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 1, 0.99, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 2 || _SelectionType == 3)
							{
								__MEMORY_CHECK__
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											
											__MEMORY_CHECK__
											Vertex_Rotate(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), -0.01, 0, 0);
											//Vertex_Rotate(_World._Meshs[_SelectedData[i]->meshIndex]->_VertexRendererVertexArray.GetData(_SelectedData[i]->vertexIndex), Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), -0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Translate(_SelectedData[i]->vertex, 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Scale(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 1, 0.99, 1);
										};
									};
								};
							};
							break;
						};
					case VK_UP:
						{
							if(_SelectionType == 0)
							{
								if(_TransformationSetting == 1){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Rotate(_World._Meshs[i].GetPtr(), 0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Translate(_World._Meshs[i].GetPtr(), 0, 0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Scale(_World._Meshs[i].GetPtr(), 1, 1.01, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 1)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Rotate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Translate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, 0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Scale(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 1, 1.01, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 2 || _SelectionType == 3)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Rotate(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 0.01, 0, 0);

										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Translate(_SelectedData[i]->vertex, 0, 0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Scale(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 1, 1.01, 1);
										};
									};
								};
							};
							break;
						};
					case VK_LEFT:
						{
							if(_SelectionType == 0)
							{
								if(_TransformationSetting == 1){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Rotate(_World._Meshs[i].GetPtr(), 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Translate(_World._Meshs[i].GetPtr(), -0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Scale(_World._Meshs[i].GetPtr(), 0.99, 1, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 1)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Rotate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Translate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), -0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Scale(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0.99, 1, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 2 || _SelectionType == 3)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Rotate(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 0, -0.01, 0);

										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Translate(_SelectedData[i]->vertex, -0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Scale(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 0.99, 1, 1);
										};
									};
								};
							};
							break;
						};
					case VK_RIGHT:
						{
							if(_SelectionType == 0)
							{
								if(_TransformationSetting == 1){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Rotate(_World._Meshs[i].GetPtr(), 0, 0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Translate(_World._Meshs[i].GetPtr(), 0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Scale(_World._Meshs[i].GetPtr(), 1.01, 1, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 1)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Rotate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, 0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Translate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Scale(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 1.01, 1, 1, true);
										};
									};
								};
							}
							else if(_SelectionType == 2 || _SelectionType == 3)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Rotate(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 0, 0.01, 0);

										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Translate(_SelectedData[i]->vertex, 0.01, 0, 0);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Scale(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 1.01, 1, 1);
										};
									};
								};
							};
							break;
						};
						//page up
					case VK_PRIOR:
						{
							if(_SelectionType == 0)
							{
								if(_TransformationSetting == 1){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Rotate(_World._Meshs[i].GetPtr(), 0, 0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Translate(_World._Meshs[i].GetPtr(), 0, 0, 0.01);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Scale(_World._Meshs[i].GetPtr(), 1, 1, 1.01, true);
										};
									};
								};
							}
							else if(_SelectionType == 1)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Rotate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, 0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Translate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, 0, 0.01);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Scale(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 1, 1, 1.01, true);
										};
									};
								};
							}
							else if(_SelectionType == 2 || _SelectionType == 3)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Rotate(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 0, 0.01, 0);

										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Translate(_SelectedData[i]->vertex, 0, 0, 0.01);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Scale(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 1, 1, 1.01);
										};
									};
								};
							};
							break;
						};
						//page down
					case VK_NEXT:
						{
							if(_SelectionType == 0)
							{
								if(_TransformationSetting == 1){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Rotate(_World._Meshs[i].GetPtr(), 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Translate(_World._Meshs[i].GetPtr(), 0, 0, -0.01);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_World.GetNumberOfMeshs() > 0)
									{
										for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
										{
											Model_Scale(_World._Meshs[i].GetPtr(), 1, 1, 0.99, true);
										};
									};
								};
							}
							else if(_SelectionType == 1)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Rotate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Translate(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 0, 0, -0.01);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Model_Scale(_World._Meshs[_SelectedData[i]->meshIndex].GetPtr(), 1, 1, 0.99, true);
										};
									};
								};
							}
							else if(_SelectionType == 2 || _SelectionType == 3)
							{
								if(_TransformationSetting == 1){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Rotate(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 0, -0.01, 0);
										};
									};
								}
								else if(_TransformationSetting == 0){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Translate(_SelectedData[i]->vertex, 0, 0, -0.01);
										};
									};
								}
								else if(_TransformationSetting == 2){
									if(_SelectedData.GetSize() > 0)
									{
										for(int i = 0; i < _SelectedData.GetSize(); i++)
										{
											Vertex_Scale(_SelectedData[i]->vertex, Point3D(_World._Meshs[_SelectedData[i]->meshIndex]->_X, _World._Meshs[_SelectedData[i]->meshIndex]->_Y, _World._Meshs[_SelectedData[i]->meshIndex]->_Z), 1, 1, 0.99);
										};
									};
								};
							};
							break;
						};
					case 0x43:
						{
							_CreationSetting = true;
							break;
						};
					case 0x31:
						{
							if(_CreationSetting)
							{
								Mesh mesh;
								Create_Cube(&mesh, 0.5);
								v5String name = "Cube";
								name += v5String::ToString((uint)_World.GetNumberOfMeshs());
								mesh.SetName(name);
								name.Clear();
								_World.AddMesh(mesh);
								mesh.Clear();
								_CreationSetting = false;
							}
							else if(GetAsyncKeyState(VK_CONTROL))
							{
								//ClearSelectedData();
								_SelectionType = 0;
							};
							break;
						};
					case 0x32:
						{
							if(_CreationSetting)
							{
								Mesh mesh;
								CreateSphere(&mesh, 15, 15, 0.5);
								v5String name = "Sphere";
								name += v5String::ToString((uint)_World.GetNumberOfMeshs());
								mesh.SetName(name);
								name.Clear();
								_World.AddMesh(mesh);
								mesh.Clear();
								_CreationSetting = false;
							}
							else if(GetAsyncKeyState(VK_CONTROL))
							{
								ClearSelectedData();
								_SelectionType = 1;
							};
							break;
						};
					case 0x33:
						{
							if(_CreationSetting)
							{
								Mesh mesh;
								CreateTorus(&mesh, 0.5, 0.25, 15, 15);
								v5String name = "Torus";
								name += v5String::ToString((uint)_World.GetNumberOfMeshs());
								mesh.SetName(name);
								name.Clear();
								_World.AddMesh(mesh);
								mesh.Clear();
								_CreationSetting = false;
							}
							else if(GetAsyncKeyState(VK_CONTROL))
							{
								ClearSelectedData();
								_SelectionType = 2;
							};
							break;
						};
					case 0x34:
						{
							if(_CreationSetting)
							{
								Mesh mesh;
								Create_Plane(&mesh, 15, 15, 0.5, true);
								v5String name = "Plane";
								name += v5String::ToString((uint)_World.GetNumberOfMeshs());
								mesh.SetName(name);
								name.Clear();
								_World.AddMesh(mesh);
								mesh.Clear();
								_CreationSetting = false;
							}
							else if(GetAsyncKeyState(VK_CONTROL))
							{
								ClearSelectedData();
								_SelectionType = 3;
							};
							break;
					};
					case 0x35:
					{
								 Edge_Split(_World._Meshs[0].GetPtr(), _SelectedData[0]->vertex, _SelectedData[1]->vertex);
								 _SelectedData.Clear();
								 break;
					};
					case 0x36:
					{
								 Fuse_Vertices(_World._Meshs[0].GetPtr(), _SelectedData[0]->vertex, _SelectedData[1]->vertex);
								 _SelectedData.Clear();
								 break;
					};

					case 0x4C:
						{
							if(GetAsyncKeyState(VK_CONTROL))
							{
								if(!_Loading)
								{
									_Loading = true;
									SetWindowText(hWnd, "Nuke - 3D Modeling :: LOADING!");
									ShowWindow(_LoadButtonHandlePtr, SW_SHOW);
									ShowWindow(_SaveButtonHandlePtr, SW_HIDE);
									if(_SaveLoadWindowPtr != null)_SaveLoadWindowPtr->Show();
								};
							};
							break;
						};
					case 0x4E:
						{
							if(GetAsyncKeyState(VK_CONTROL))
							{
								_World.Clear();
							};
							break;
						};
					};
					
					break;
				};
			case WM_LBUTTONDOWN:
				{
					if (_SelectionType == 0)
					{
						ClearSelectedData();
					}; 
					float y = HIWORD(lParam);
					float x = LOWORD(lParam);
					Coordinates xy = ConvertScreenCoordsToWorldCoords(Coordinates(x, y), _MainWindowPtr->GetWidth(), _MainWindowPtr->GetHeight());
					y += 20;
					if(_SelectionType == 1)
					{
						for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
						{
							int index =  Face_Select(_World._Meshs[i].GetPtr(), xy.X, xy.Y);
							if(index > -1)
							{
								SelectionData data1 = { i, null };
								_SelectedData.Add(data1);
								uint number = _World._Meshs[i]->GetNumberOfVertices();
								for (int j = 0; j < number; j++)
								{
									_World._Meshs[i]->GetVertex(j)->Color = D3DXCOLOR(1, 0, 0, 1);
								};
							};
							//_World._Meshs[i]->_VertexRendererUpdate = true;
						};
					}
					else if(_SelectionType == 2)
					{
						for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
						{
							int index = Face_Select(_World._Meshs[i].GetPtr(), x, y);

							if (index > -1)
							{
								TriangleFace face = _World._Meshs[i]->GetNthTriangleFace(index);
								SelectionData data1 = { i, face.GetVertex1() };
								SelectionData data2 = { i, face.GetVertex2() };
								SelectionData data3 = { i, face.GetVertex3() };
								_SelectedData.Add(data1);
								_SelectedData.Add(data2);
								_SelectedData.Add(data3);
								face.GetVertex1()->Color = D3DXCOLOR(1, 0, 0, 1);
								face.GetVertex2()->Color = D3DXCOLOR(1, 0, 0, 1);
								face.GetVertex3()->Color = D3DXCOLOR(1, 0, 0, 1);
							};
								//_World._Meshs[i]->_VertexRendererUpdate = true;
							//};
						};
					}
					else if(_SelectionType == 3)
					{
						for(int i = 0; i < _World.GetNumberOfMeshs(); i++)
						{
							Vertex* vert = Vertex_Select(_World._Meshs[i]->GetVertexArrayDirect(), x, y, 20);
							if(vert != null)
							{
								SelectionData data = {i, vert};
								_SelectedData.Add(data);
								vert->Color = D3DXCOLOR(1, 0, 0, 1);
								//_World._Meshs[i]->_VertexRendererUpdate = true;
							};
						};
					}

					break;
				};
		};

		return DefWindowProc(hWnd, message, wParam, lParam);
	};

	LRESULT CALLBACK SaveLoadWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
		case WM_COMMAND:
			{
				switch(LOWORD(wParam))
				{
				case 1:
					{
						char buffer[256];
						GetWindowText(_SaveLoadTextBoxHandlePtr, buffer, 256);
						v5String path = _WorldFolder;
						path += buffer;
						SetWindowText(hWnd, "Initializing Save!");
						_World.SaveAs(path, _SaveLoadWindowPtr->GetHandle());
						_Saving = false;
						_SavingDone = true;
						_SaveLoadWindowPtr->Hide();
						break;
					};
				case 2:
					{
						char buffer[256];
						GetWindowText(_SaveLoadTextBoxHandlePtr, buffer, 256);
						v5String path = _WorldFolder;
						path += buffer;
						SetWindowText(hWnd, "Preparing To Load World!");
						_World.Load(path, _SaveLoadWindowPtr->GetHandle());
						_Loading = false;
						_LoadingDone = true;
						_SaveLoadWindowPtr->Hide();
						break;
					};
					break;
				};
				break;
			};
			break;
		};
		return DefWindowProc(hWnd, message, wParam, lParam);
	};

	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		int __MEMORY_CHECK_ORIGINAL_SETTINGS__ = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); 
		int __MEMORY_CHECK_MODIFIED_SETTINGS__ = __MEMORY_CHECK_ORIGINAL_SETTINGS__; 
		__MEMORY_CHECK_MODIFIED_SETTINGS__ = (__MEMORY_CHECK_MODIFIED_SETTINGS__ & 0x0000FFFF) | 0x00010000 | _CRTDBG_CHECK_ALWAYS_DF; 
		_CrtSetDbgFlag(__MEMORY_CHECK_MODIFIED_SETTINGS__); 
		
		__MEMORY_CHECK__
		_SaveLoadTextBoxHandlePtr = null;
		__MEMORY_CHECK__

		Window wind("Nuke - 3D Modeling", "Nuke - 3D Modeling", hInstance, WindowProc, nCmdShow, 0, 0, 600, 600);
		__MEMORY_CHECK__
		_MainWindowPtr = &wind;
		__MEMORY_CHECK__ 

		Window saveLoad("SAVE", "SAVE", hInstance, SaveLoadWindowProc, nCmdShow, 10, 10, 700, 100);
		__MEMORY_CHECK__
		_SaveLoadTextBoxHandlePtr = CreateWindow("Edit","The world name that you wish to load/save", WS_CHILD | WS_VISIBLE | SS_LEFT,  40,40, 640,20, saveLoad.GetHandle(), NULL, hInstance, NULL);
		__MEMORY_CHECK__
		CreateWindow("Button", "Save", WS_CHILD | WS_VISIBLE, 0, 0, 35, 30, saveLoad.GetHandle(), (HMENU)1, hInstance, null);
		__MEMORY_CHECK__
		CreateWindow("Button", "Load", WS_CHILD | WS_VISIBLE,36, 0, 35, 30, saveLoad.GetHandle(), (HMENU)2, hInstance, null);
		__MEMORY_CHECK__
		_SaveLoadWindowPtr = &saveLoad;
		__MEMORY_CHECK__
		saveLoad.Hide();
		__MEMORY_CHECK__

			v5RenderState renderState(&wind);
		__MEMORY_CHECK__
		SolidRenderer renderer(&renderState);
		__MEMORY_CHECK__
		WireframeRenderer wirerenderer(&renderState);
		__MEMORY_CHECK__
		VertexRenderer  vertexRenderer(&renderState);
		__MEMORY_CHECK__

		MSG msg;
		while(!__IS_EXITING__)
		{
			__MEMORY_CHECK__
			//translate messages
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			};

			if(msg.message == WM_QUIT)
			{
				break;
			};
			
			if(_SavingDone)
			{
				_SavingDone = false;
				SetWindowText(wind.GetHandle(), "Nuke - 3D Modeling");
				__MEMORY_CHECK__
			};
			if(_LoadingDone)
			{
				_LoadingDone = false;
				SetWindowText(wind.GetHandle(), "Nuke - 3D Modeling");
				__MEMORY_CHECK__
			};
			if(!_Saving && !_Loading)
			{
				renderState.ClearDisplay();
				__MEMORY_CHECK__
				renderer.Draw(&_World);
				__MEMORY_CHECK__
				wirerenderer.Draw(&_World);
				__MEMORY_CHECK__
					renderState.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
				vertexRenderer.Draw(&_World);
				renderState.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				__MEMORY_CHECK__
				renderState.Present();
				__MEMORY_CHECK__
			};
		};
		__MEMORY_CHECK__
		_World.Release();
		__MEMORY_CHECK__
		return msg.wParam;
	};