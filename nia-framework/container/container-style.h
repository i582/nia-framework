#pragma once

#include "SDL.h"

#include "../utils/color.h"

#include "container-style-raw.h"

using color = Uint32;

class ContainerStyle
{
private:
	/*
	 * Background
	 */
	Color _backgroundColor;
	Color _hoverBackgroundColor;
	Color _activeBackgroundColor;

	/*
	 * Border
	 */
	Color _borderColor;
	Color _hoverBorderColor;
	Color _activeBorderColor;

	/*
	 * Cursor
	 */
	SDL_Cursor* _cursor;
	SDL_Cursor* _hoverCursor;


public:
	ContainerStyle();

public:
	friend ContainerStyleRaw;


public:
	color backgroundColor();
	color hoverBackgroundColor();
	color activeBackgroundColor();

	color borderColor();
	color hoverBorderColor();
	color activeBorderColor();


	/*SDL_Cursor* cursor();
	SDL_Cursor* hoverCursor();*/
};