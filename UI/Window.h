#include "Global_Variables.H"

#ifndef __UI_WINDOW__
#define __UI_WINDOW__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace UI
		{
			using namespace BrokenTechStudios::Nuke::Core;

			class Window
			{
			private:
				WNDCLASSEX _WindowClass;
				HWND _Handle;
				float _X;
				float _Y;
				float _Width;
				float _Height;
			public:
				Window(){};

				Window(LPCSTR windowClassName, LPCSTR windowTitleString, HINSTANCE hInstance, WNDPROC windowProc, int nCmdShow, float x, float y, float width, float height)
				{
					_X = x;
					_Y = y;
					_Width = width;
					_Height = height;
					ZeroMemory(&_WindowClass, sizeof(WNDCLASSEX));

					_WindowClass.cbSize = sizeof(WNDCLASSEX);
					_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
					_WindowClass.lpfnWndProc = windowProc;
					_WindowClass.hInstance = hInstance;
					_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
					_WindowClass.lpszClassName = windowClassName;

					RegisterClassEx(&_WindowClass);


					_Handle = CreateWindowEx(null, windowClassName, windowTitleString, WS_OVERLAPPEDWINDOW, x, y, width, height, null, null, hInstance, null);

					ShowWindow(_Handle, nCmdShow);
				};

				~Window()
				{
					DestroyWindow(_Handle);
				};

				float GetX(){return _X;};
				float GetY(){return _Y;};
				float GetWidth(){return _Width;};
				float GetHeight(){return _Height;};
				HWND GetHandle(){return _Handle;};
				void Show(){ShowWindow(_Handle, SW_SHOW);};
				void Hide(){ShowWindow(_Handle, SW_HIDE);};
			};
		};
	};
};

#endif