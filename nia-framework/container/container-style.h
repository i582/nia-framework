#pragma once

#include "SDL.h"

#include "../utils/color.h"
#include "../utils/shadow.h"
#include "../font/font.h"

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

	/*
	 * Shadow
	 */
	Shadow _shadow;


	/**
	 * Text
	 */
	size_t _textSize;
	double _textLineHeight;
	Font _textFont;
	Color _textColor;
	Color _hoverTextColor;
	Color _activeTextColor;


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

	Shadow shadow();
	/*SDL_Cursor* cursor();
	SDL_Cursor* hoverCursor();*/

	/**
	 * Text
	 */
	size_t textSize();
	double textLineHeight();
	Font textFont();
	Color textColor();
	Color hoverTextColor();
	Color activeTextColor();
};