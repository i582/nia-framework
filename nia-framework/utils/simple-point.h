#pragma once

#include "SDL.h"

class SimplePoint
{
public:
	int x, y;

public:
	SDL_Point toSdlPoint();
};