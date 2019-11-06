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
