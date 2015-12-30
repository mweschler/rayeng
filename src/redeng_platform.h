#ifndef _REDENG_PLATFORM_H_
#define _REDENG_PLATFORM_H_

struct game_back_buffer
{
	void *Memory;
	int Width;
	int Height;
	int Pitch;
	int BytesPerPixel;
};

void DebugLog(char* text);

#endif