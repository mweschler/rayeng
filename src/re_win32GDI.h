#ifndef _REDENG_WIN32_GDI_H_
#define _REDENG_WIN32_GDI_H_

#include <wingdi.h>

struct win32_back_buffer
{
	BITMAPINFO Info;
	void *Memory;
	int Width;
	int Height;
	int Pitch;
	int BytesPerPixel;
};

void Win32DrawBackBuffer(win32_back_buffer *Buffer, HDC DeviceContext, int WindowWidth, int WindowHeight);
void Win32ResizeBackBuffer(win32_back_buffer *Buffer, int Width, int Height);
void Win32ClearBackBuffer(win32_back_buffer *Buffer);

#endif