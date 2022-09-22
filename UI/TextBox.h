#include "Global_Variables.h"
#include "Window.h"

#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

namespace BrokenTechStudios
{
	namespace Nuke
	{
		namespace UI
		{
			using namespace BrokenTechStudios::Nuke::Core;

			struct TextBox
			{
				HWND _Handle;
				TextBox(){};
				TextBox(int x, int y, int width, int height, HWND parrentWindowHandle)
				{
					_Handle = CreateWindow(TEXT("EDIT"), null, WS_CHILD | WS_VISIBLE, x, y, width, height, parrentWindowHandle, null, null, null);
				};
				TextBox(int x, int y, int width, int height, HWND parrentWindowHandle, int id)
				{
					_Handle = CreateWindow(TEXT("EDIT"), null, WS_CHILD | WS_VISIBLE, x, y, width, height, parrentWindowHandle, (HMENU)id, null, null);
				};
				~TextBox()
				{
					DestroyWindow(_Handle);
				};
			};
		};
	};
};
#endif