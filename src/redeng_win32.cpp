#include <Windows.h>

#include "core.h"
#include "redeng_platform.h"
#include "re_win32GDI.h"
#include "raygame.h"

static bool sIsRunning = true;
static win32_back_buffer sBackBuffer = {};

static int32 sWindowWidth = 800;
static int32 sWindowHeight = 600;

void DebugLog(char* text)
{
	OutputDebugString(text);
}

LRESULT CALLBACK WndProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT Result = 0;

	switch (Message)
	{
	case WM_CLOSE:
	{
		sIsRunning = false;
	} break;

	case WM_DESTROY:
	{
		sIsRunning = false;
	} break;

	case WM_PAINT:
	{
		PAINTSTRUCT Paint;
		HDC DeviceContext = BeginPaint(Window, &Paint);
		Win32DrawBackBuffer(&sBackBuffer, DeviceContext, sWindowWidth, sWindowHeight);
		EndPaint(Window, &Paint);
	} break;


	default:
	{
		Result = DefWindowProcA(Window, Message, WParam, LParam);
	} break;
	}

	return(Result);
}


int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE UNREF(PrevInstance), LPSTR UNREF(CommandLine), int UNREF(ShowCode))
{
	WNDCLASSA WindowClass = {};

	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.hInstance = Instance;
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	WindowClass.lpszClassName = "RedEngWindowClass";

	if (RegisterClassA(&WindowClass))
	{
		HWND Window =
			CreateWindowExA(0, WindowClass.lpszClassName, "RedEng",	WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
				CW_USEDEFAULT, CW_USEDEFAULT, sWindowWidth, sWindowHeight, 0, 0, Instance, 0);
		if (Window)
		{ 
			Win32ResizeBackBuffer(&sBackBuffer, sWindowWidth, sWindowHeight);

			LARGE_INTEGER frequency;
			if (!QueryPerformanceFrequency(&frequency))
			{
				//handle error
			}

			LARGE_INTEGER start;
			QueryPerformanceCounter(&start);

			while (sIsRunning)
			{
				MSG Message;
				while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessageA(&Message);
				}

				game_back_buffer BackBuffer = {};
				BackBuffer.Memory = sBackBuffer.Memory;
				BackBuffer.Width = sBackBuffer.Width;
				BackBuffer.Height = sBackBuffer.Height;
				BackBuffer.Pitch = sBackBuffer.Pitch;
				BackBuffer.BytesPerPixel = sBackBuffer.BytesPerPixel;

				LARGE_INTEGER end;
				QueryPerformanceCounter(&end);
				float elapsedMS = (static_cast<float>(end.QuadPart - start.QuadPart) / frequency.QuadPart) * 1000.0f;
				start = end;

				RayGame(elapsedMS);

				Win32ClearBackBuffer(&sBackBuffer);
				RayRender(BackBuffer);

				HDC DeviceContext = GetDC(Window);
				Win32DrawBackBuffer(&sBackBuffer, DeviceContext, sWindowWidth, sWindowHeight);
				ReleaseDC(Window, DeviceContext);
			}
		}
		else
		{
			//Do Error
		}
	}
	else
	{
		//Do error
	}
	return 0;
}