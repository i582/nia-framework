#pragma once

#include "string"
#include "map"

using std::string;
using std::map;

class ContainerStyle;

class ContainerStyleRaw
{
private:
	/*
	 * Background
	 */
	string _backgroundColor;
	string _hoverBackgroundColor;
	string _activeBackgroundColor;

	/*
	 * Border
	 */
	string _borderColor;
	string _hoverBorderColor;
	string _activeBorderColor;

	/*
	 * Cursor
	 */
	string _cursor;
	string _hoverCursor;


	/*
	 * Shadow
	 */
	string _shadow;

public:

	/*
	 * @brief Setup all style is none
	 */
	ContainerStyleRaw();

	/*
	 * @brief Setup standart style
	 */
	ContainerStyleRaw(bool standart);

public:
	void updateStyle(ContainerStyle* style);


public:
	string backgroundColor();
	string hoverBackgroundColor();
	string activeBackgroundColor();

	ContainerStyleRaw* backgroundColor(string newColor);
	ContainerStyleRaw* hoverBackgroundColor(string newColor);
	ContainerStyleRaw* activeBackgroundColor(string newColor);


	string borderColor();
	string hoverBorderColor();
	string activeBorderColor();

	ContainerStyleRaw* borderColor(string newColor);
	ContainerStyleRaw* hoverBorderColor(string newColor);
	ContainerStyleRaw* activeBorderColor(string newColor);

	string cursor();
	string hoverCursor();

	ContainerStyleRaw* cursor(string cursor_id);
	ContainerStyleRaw* hoverCursor(string cursor_id);


	string shadow();
	ContainerStyleRaw* shadow(string shadow);
};

using Style = ContainerStyleRaw;