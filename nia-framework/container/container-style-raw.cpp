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
}

ContainerStyleRaw::ContainerStyleRaw(bool standart)
{
	/*
	 * Background standart color
	 */
	this->_backgroundColor = 
	this->_hoverBackgroundColor = 
	this->_activeBackgroundColor = "#FFFFFF";
	
	/*
	 * Border standart color
	 */
	this->_borderColor = 
	this->_hoverBorderColor = 
	this->_activeBorderColor = "#FFFFFF00";

	/*
	 * Cursor standart
	 */
	this->_cursor =
	this->_hoverCursor = "arrow";

	/*
	 * Shadow
	 */
	this->_shadow = "none";
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

	if (_hoverBorderColor != "none")
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
	_backgroundColor = newColor;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::hoverBackgroundColor(string newColor)
{
	_hoverBackgroundColor = newColor;
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
	_borderColor = newColor;
	return this;
}

ContainerStyleRaw* ContainerStyleRaw::hoverBorderColor(string newColor)
{
	_hoverBorderColor = newColor;
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
