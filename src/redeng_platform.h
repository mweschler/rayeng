#ifndef _REDENG_PLATFORM_H_
#define _REDENG_PLATFORM_H_

struct game_back_buffer
{
	// NOTE(casey): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
	void *Memory;
	int Width;
	int Height;
	int Pitch;
	int BytesPerPixel;
};

#endif