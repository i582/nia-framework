#include "container-style-raw.h"
#include "container-style.h"

ContainerStyleRaw::ContainerStyleRaw()
{
	/*
	 * Background none color
	 */
	this->_backgroundColor =
	this->_hoverBackgroundColor =
	this->_activeBackgroundColor = "none";

	/*
	 * Border none color
	 */
	this->_borderColor =
	this->_hoverBorderColor =
	this->_activeBorderColor = "none";

	/*
	 * Cursor none
	 */
	this->_cursor =
	this->_hoverCursor = "none";

	/*
	 * Shadow
	 */
	this->_shadow = "none";

	/**
	 * Text
	 */
	this->_textSize = "none";
	this->_textLineHeight = "none";
	this->_textFont = "none";
	this->_textColor =
	this->_hoverTextColor =
	this->_activeTextColor = "none";
}

ContainerStyleRaw::ContainerStyleRaw(bool standart)
{
	/**
	 * Background standart color
	 */
	this->_backgroundColor = 
	this->_hoverBackgroundColor = 
	this->_activeBackgroundColor = "#FFFFFF";
	
	/**
	 * Border standart color
	 */
	this->_borderColor = 
	this->_hoverBorderColor = 
	this->_activeBorderColor = "#FFFFFF00";

	/**
	 * Cursor standart
	 */
	this->_cursor =
	this->_hoverCursor = "arrow";

	/**
	 * Shadow
	 */
	this->_shadow = "none";

	/**
	 * Text
	 */
	this->_textSize = "14px";
	this->_textLineHeight = "1.3";
	this->_textFont = "consolas";
	this->_textColor =
	this->_hoverTextColor =
	this->_activeTextColor = "#000000";
}

void ContainerStyleRaw::updateStyle(ContainerStyle* style)
{

	if (_backgroundColor != "none")
	{
		style->_backgroundColor = Color(_backgroundColor);
	}

	if (_hoverBackgroundColor != "none")
	{
		style->_hoverBackgroundColor = Color(_hoverBackgroundColor);
	}

	if (_activeBackgroundColor != "none")
	{
		style->_activeBackgroundColor = Color(_activeBackgroundColor);
	}


	if (_borderColor != "none")
	{
		style->_borderColor = Color(_borderColor);
	}

	if (_hoverBorderColor != "none")
	{
		style->_hoverBorderColor = Color(_hoverBorderColor);
	}

	if (_activeBorderColor != "none")
	{
		style->_activeBorderColor = Color(_activeBorderColor);
	}


	if (_shadow != "none")
	{
		style->_shadow = Shadow(_shadow);
	}


	if (_cursor != "none")
	{
		if (_cursor == "arrow")
		{
			style->_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		}
		else if (_cursor == "hand")
		{
			style->_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		}
	}

	if (_hoverCursor != "none")
	{
		if (_hoverCursor == "arrow")
		{
			style->_hoverCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		}
		else if (_hoverCursor == "hand")
		{
			style->_hoverCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		}
	}



	if (_textSize != "none")
		style->_textSize = Utils::to_integer(_textSize);
	
	if (_textLineHeight != "none")
		style->_textLineHeight = Utils::to_double(_textLineHeight);
	
	if (_textColor != "none")
		style->_textColor = Color(_textColor);
	
	if (_hoverTextColor != "none")
		style->_hoverTextColor = Color(_hoverTextColor);

	if (_activeTextColor != "none")
		style->_activeTextColor = Color(_activeTextColor);
}





string ContainerStyleRaw::backgroundColor()
{
	return _backgroundColor;
}

string ContainerStyleRaw::hoverBackgroundColor()
{
	return _hoverBackgroundColor;
}

string ContainerStyleRaw::activeBackgroundColor()
{
	return _activeBackgroundColor;
}



ContainerStyleRaw* ContainerStyleRaw::backgroundColor(string newColor)
{
	_backgroundColor = _hoverBackgroundColor = _activeBackgroundColor= newColor;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::hoverBackgroundColor(string newColor)
{
	_hoverBackgroundColor = _activeBackgroundColor = newColor;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::activeBackgroundColor(string newColor)
{
	_activeBackgroundColor = newColor;
	return this;
}



string ContainerStyleRaw::borderColor()
{
	return _borderColor;
}

string ContainerStyleRaw::hoverBorderColor()
{
	return _hoverBorderColor;
}

string ContainerStyleRaw::activeBorderColor()
{
	return _activeBorderColor;
}



ContainerStyleRaw* ContainerStyleRaw::borderColor(string newColor)
{
	_borderColor = _hoverBorderColor = _activeBorderColor = newColor;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::hoverBorderColor(string newColor)
{
	_hoverBorderColor = _activeBorderColor = newColor;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::activeBorderColor(string newColor)
{
	_activeBorderColor = newColor;
	return this;
}



string ContainerStyleRaw::cursor()
{
	return _cursor;
}

ContainerStyleRaw* ContainerStyleRaw::cursor(string cursor_id)
{
	_cursor = cursor_id;
	return this;
}

string ContainerStyleRaw::hoverCursor()
{
	return _hoverCursor;
}

ContainerStyleRaw* ContainerStyleRaw::hoverCursor(string cursor_id)
{
	_hoverCursor = cursor_id;
	return this;
}

string ContainerStyleRaw::shadow()
{
	return _shadow;
}

ContainerStyleRaw* ContainerStyleRaw::shadow(string shadow)
{
	_shadow = shadow;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::textSize(string value)
{
	_textSize = value;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::textFont(string value)
{
	_textFont = value;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::textLineHeight(string value)
{
	_textLineHeight = value;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::textColor(string value)
{
	_textColor = _hoverTextColor = _activeTextColor = value;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::hoverTextColor(string value)
{
	_hoverTextColor = _activeTextColor = value;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::activeTextColor(string value)
{
	_activeTextColor = value;
	return this;
}

string ContainerStyleRaw::textSize()
{
	return _textSize;
}

string ContainerStyleRaw::textLineHeight()
{
	return _textLineHeight;
}

string ContainerStyleRaw::textFont()
{
	return _textFont;
}

string ContainerStyleRaw::textColor()
{
	return _textColor;
}

string ContainerStyleRaw::hoverTextColor()
{
	return _hoverTextColor;
}

string ContainerStyleRaw::activeTextColor()
{
	return _activeTextColor;
}
