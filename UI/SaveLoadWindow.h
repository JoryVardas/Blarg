#include "Window.h"
#include "v5String.h"
#include "Button.h"
#include "TextBox.h"

#ifndef __SAVE_LOAD_WINDOW_H__
#define __SAVE_LOAD_WINDOW_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace UI
		{
			using namespace BrokenTechStudios::Nuke::Core;

			static v5String __SAVE_LOAD_WINDOW_OUTPUT__;
			static bool __SAVE_LOAD_WINDOW_OUTPUT_COMPLETE__ = false;
			static HWND* __SAVE_LOAD_TEXTBOX_HANDLE__;
			LRESULT CALLBACK SaveLoadWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
			{
				switch(message)
				{
				case WM_DESTROY:
					{
						PostQuitMessage(0);
						return 0;
						break;
					};
				case WM_COMMAND:
					{
						switch(LOWORD(wParam))
						{
						case 1:
							char buffer[256];
							GetWindowText(*__SAVE_LOAD_TEXTBOX_HANDLE__, buffer, 256);
							__SAVE_LOAD_WINDOW_OUTPUT__ = buffer;
							__SAVE_LOAD_WINDOW_OUTPUT_COMPLETE__ = true;
							break;
						};
						break;
					};
				};
				return DefWindowProc(hWnd, message, wParam, lParam);
			};

			class SaveLoadWindow
			{
			private:
				WNDCLASSEX _WindowClass;
				HWND _Handle;
				float _X;
				float _Y;
				float _Width;
				float _Height;
			public:
				SaveLoadWindow(){};

				SaveLoadWindow(bool SaveLoad, HINSTANCE hInstance, int nCmdShow, float x, float y, float width, float height)
				{
					_X = x;
					_Y = y;
					_Width = width;
					_Height = height;
					ZeroMemory(&_WindowClass, sizeof(WNDCLASSEX));

					_WindowClass.cbSize = sizeof(WNDCLASSEX);
					_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
					_WindowClass.lpfnWndProc = SaveLoadWindowProc;
					_WindowClass.hInstance = hInstance;
					_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
					if(SaveLoad)_WindowClass.lpszClassName = "SaveWindow";
					else _WindowClass.lpszClassName = "LoadWindow";

					RegisterClassEx(&_WindowClass);


					if(SaveLoad)_Handle = CreateWindowEx(null, "SaveWindow", "Save", WS_OVERLAPPEDWINDOW, x, y, width, height, null, null, hInstance, null);
					else _Handle = CreateWindowEx(null, "LoadWindow", "Load", WS_OVERLAPPEDWINDOW, x, y, width, height, null, null, hInstance, null);

					ShowWindow(_Handle, nCmdShow);
					
					//TextBox tb(0, 0, width - 30, height, _Handle, 0);
					//__SAVE_LOAD_TEXTBOX_HANDLE__ = &tb._Handle;
					//if(SaveLoad)
					//{
						Button("Save", 0, 0, 50, 25, _Handle, 1);
					//}
					//else
					//{
					//	Button("Load", width - 25, 0, 25, height, _Handle, 1);
					//};
				};

				~SaveLoadWindow()
				{
					Destroy();
				};

				void Destroy()
				{
					DestroyWindow(_Handle);
					__SAVE_LOAD_TEXTBOX_HANDLE__ = null;
					__SAVE_LOAD_WINDOW_OUTPUT__ = "";
					__SAVE_LOAD_WINDOW_OUTPUT_COMPLETE__ = false;
				};

				float GetX(){return _X;};
				float GetY(){return _Y;};
				float GetWidth(){return _Width;};
				float GetHeight(){return _Height;};
				HWND GetHandle(){return _Handle;};

				bool WaitForOutputThenClose()
				{
					MSG msg;
					while(!__SAVE_LOAD_WINDOW_OUTPUT_COMPLETE__)
					{
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
					};
					return __SAVE_LOAD_WINDOW_OUTPUT_COMPLETE__;
				};
			};
		};
	};
};

#endif