#pragma once

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#include "../utils/color.h"

namespace Draw
{

	void circle(SDL_Renderer* renderer, int x, int y, int r, Uint32 color);
	void circle(SDL_Renderer* renderer, int x, int y, int r, Uint32 color, size_t thickness);

	void circle(SDL_Renderer* renderer, int x, int y, int r, Uint32 start_color, Uint32 end_color, size_t thickness);


	void arc(SDL_Renderer* renderer, int x, int y, int r, Uint32 color, size_t arc_num);
	void arc(SDL_Renderer* renderer, int x, int y, int r, Uint32 color, size_t arc_num, size_t thickness);

	void arc(SDL_Renderer* renderer, int x, int y, int r, Uint32 start_color, Uint32 end_color, size_t arc_num, size_t thickness);

	void hline(SDL_Renderer* renderer, int x1, int y, int x2, Uint32 start_color, Uint32 end_color, size_t thickness);
	void vline(SDL_Renderer* renderer, int x, int y1, int y2, Uint32 start_color, Uint32 end_color, size_t thickness);


	void roundedShadowRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int r, Uint32 start_color, Uint32 end_color, size_t shadowThickness, size_t shadowStart = 0);


	void roundedRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int r, Uint32 color);


	void hline(SDL_Renderer* renderer, int x1, int y, int x2, Uint32 color);
	void vline(SDL_Renderer* renderer, int x, int y1, int y2, Uint32 color);
}