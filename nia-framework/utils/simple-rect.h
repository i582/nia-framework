#pragma once

#include "SDL.h"

class SimpleRect
{
public:
	int x, y;
	int w, h;

public:
	SDL_Rect toSdlRect();
};