#include "container-style.h"

ContainerStyle::ContainerStyle()
{
	this->_backgroundColor = 
	this->_hoverBackgroundColor = 
	this->_activeBackgroundColor = 0xffffffff;

	this->_borderColor = 
	this->_hoverBorderColor = 
	this->_activeBorderColor = 0x00000000;

	this->_cursor = 
	this->_hoverCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

	this->_textSize = 14;
	this->_textLineHeight = 1.3;
	this->_textFont = *new Font();
	this->_textColor =
	this->_hoverTextColor =
	this->_activeTextColor = 0x00000000;
}



color ContainerStyle::backgroundColor()
{
	return _backgroundColor.color();
}

color ContainerStyle::hoverBackgroundColor()
{
	return _hoverBackgroundColor.color();
}

color ContainerStyle::activeBackgroundColor()
{
	return _activeBackgroundColor.color();
}


color ContainerStyle::borderColor()
{
	return _borderColor.color();
}

color ContainerStyle::hoverBorderColor()
{
	return _hoverBorderColor.color();
}

color ContainerStyle::activeBorderColor()
{
	return _activeBorderColor.color();
}

Shadow ContainerStyle::shadow()
{
	return _shadow;
}

size_t ContainerStyle::textSize()
{
	return _textSize;
}

double ContainerStyle::textLineHeight()
{
	return _textLineHeight;
}

Font ContainerStyle::textFont()
{
	return _textFont;
}

Color ContainerStyle::textColor()
{
	return _textColor;
}

Color ContainerStyle::hoverTextColor()
{
	return _hoverTextColor;
}

Color ContainerStyle::activeTextColor()
{
	return _activeTextColor;
}
