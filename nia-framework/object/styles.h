#pragma once
#include "SDL.h"
#include "string"

using namespace std;

class Styles;

class StylesRaw
{
	string _width;
	string _height;

	string _backgroundColor;
	string _textColor;
	string _hoverBackgroundColor;
	string _activeBackgroundColor;

	string _borderColor;
	string _hoverBorderColor;
	string _activeBorderColor;

	string _cursor;
	string _hoverCursor;

public:
	Styles* compute();
};


using color = Uint32;

class Styles
{
private:
	color backgroundColor;
	color textColor;
	color hoverBackgroundColor;
	color activeBackgroundColor;

	color borderColor;
	color hoverBorderColor;
	color activeBorderColor;

	SDL_Cursor* cursor;
	SDL_Cursor* hoverCursor;
};