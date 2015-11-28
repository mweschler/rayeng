#include "core.h"
#include "raygame.h"
#include "redeng_platform.h"

struct ColorRGB {
	float R;
	float G;
	float B;
	uint32 ToU32() {
		uint32 red = static_cast<uint32>(R * 255.0f) << 16;
		uint32 green = static_cast<uint32>(G * 255.0f) << 8;
		uint32 blue = static_cast<uint32>(B * 255.0f);

		return red | green | blue;
	}
};

struct Rectangle {
	int32 top;
	int32 left;
	int32 right;
	int32 bottom;
};

void DrawRectangle(game_back_buffer *Buffer, Rectangle rect, ColorRGB color)
{
	//rect needs to be clamped to buffer
	uint32 colorValue = color.ToU32();

	uint8* row = static_cast<uint8 *>(Buffer->Memory);
	row = row + (rect.left * Buffer->BytesPerPixel);
	row = row + (rect.top * Buffer->Pitch);

	for (int y = rect.top; y < rect.bottom; ++y)
	{
		uint32* pixel = reinterpret_cast<uint32 *>(row);
		for (int x = rect.left; x < rect.right; ++x)
		{
			*pixel = colorValue;
			++pixel;
		}
		row += Buffer->Pitch;
	}
}


void RayGame()
{

}

void RayRender(game_back_buffer& BackBuffer)
{
	DrawRectangle(&BackBuffer, Rectangle{ 40, 40, 240, 240 }, ColorRGB{ 1, 0, 0 });
	DrawRectangle(&BackBuffer, Rectangle{ 40, 40, 140, 140 }, ColorRGB{ 0, 1, 0 });
}