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


	/*
	 * Text
	 */
	string _textSize;
	string _textLineHeight;
	string _textFont;
	string _textColor;
	string _hoverTextColor;
	string _activeTextColor;



public:

	/**
	 * @brief Setup all style is none
	 */
	ContainerStyleRaw();

	/**
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



	/**
	 * Text
	 */
	ContainerStyleRaw* textSize(string value);
	ContainerStyleRaw* textFont(string value);
	ContainerStyleRaw* textLineHeight(string value);
	ContainerStyleRaw* textColor(string value);
	ContainerStyleRaw* hoverTextColor(string value);
	ContainerStyleRaw* activeTextColor(string value);


	string textSize();
	string textLineHeight();
	string textFont();
	string textColor();
	string hoverTextColor();
	string activeTextColor();
};


using Style = ContainerStyleRaw;