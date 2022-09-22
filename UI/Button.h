#include "Global_Variables.h"
#include "Window.h"

#ifndef __BUTTON_H__
#define __BUTTON_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace UI
		{
			using namespace BrokenTechStudios::Nuke::Core;

			struct Button
			{
				HWND _Handle;
				Button(){};
				Button(char* text, int x, int y, int width, int height, HWND parrentWindowHandle)
				{
					_Handle = CreateWindow(TEXT("BUTTON"), text, WS_CHILD | WS_VISIBLE, x, y, width, height, parrentWindowHandle, null, null, null);
				};
				Button(char* text, int x, int y, int width, int height, HWND parrentWindowHandle, int id)
				{
					_Handle = CreateWindow(TEXT("BUTTON"), text, WS_CHILD | WS_VISIBLE, x, y, width, height, parrentWindowHandle, (HMENU)id, null, null);
				};
				~Button()
				{
					DestroyWindow(_Handle);
				};
			};
		};
	};
};
#endif