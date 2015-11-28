#include <windows.h>
#include "re_win32GDI.h"

static inline size_t BufferMemSize(win32_back_buffer *Buffer)
{
	return (Buffer->Width * Buffer->Height) * Buffer->BytesPerPixel;
}

void Win32DrawBackBuffer(win32_back_buffer *Buffer, HDC DeviceContext, int WindowWidth, int WindowHeight)
{
	StretchDIBits(DeviceContext,
		0, 0, WindowWidth, WindowHeight,
		0, 0, Buffer->Width, Buffer->Height,
		Buffer->Memory,
		&Buffer->Info,
		DIB_RGB_COLORS, SRCCOPY);
}

void Win32ResizeBackBuffer(win32_back_buffer *Buffer, int Width, int Height)
{

	if (Buffer->Memory)
	{
		VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
	}

	Buffer->Width = Width;
	Buffer->Height = Height;

	int BytesPerPixel = 4;
	Buffer->BytesPerPixel = BytesPerPixel;

	Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
	Buffer->Info.bmiHeader.biWidth = Buffer->Width;
	Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
	Buffer->Info.bmiHeader.biPlanes = 1;
	Buffer->Info.bmiHeader.biBitCount = 32;
	Buffer->Info.bmiHeader.biCompression = BI_RGB;

	size_t BitmapMemorySize = BufferMemSize(Buffer);
	Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	Buffer->Pitch = Width * BytesPerPixel;
}

void Win32ClearBackBuffer(win32_back_buffer *Buffer) 
{
	size_t BufferSize = BufferMemSize(Buffer);
	memset(Buffer->Memory, 0, BufferSize);
}
