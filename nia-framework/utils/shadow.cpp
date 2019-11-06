#include "shadow.h"

Shadow::Shadow()
{
	this->_thickness = 0;
	this->_blur = 0;
}

Shadow::Shadow(string shadowString)
{
	this->shadowString = shadowString;
	this->init();
}

void Shadow::init()
{
	vector <string>* parts = Utils::split(shadowString, ' ');

	if (parts->size() != 4)
	{
		cout << "Error shadow string" << endl;
	}

	_thickness = Utils::to_integer(parts->at(0));
	_blur = Utils::to_integer(parts->at(1));

	_start = Color(parts->at(2));
	_end = Color(parts->at(3));
}

size_t Shadow::thickness()
{
	return _thickness;
}

size_t Shadow::blur()
{
	return _blur;
}

size_t Shadow::outerSize()
{
	return _thickness > _blur ? _thickness : _blur;
}

Color Shadow::startColor()
{
	return _start;
}

Color Shadow::endColor()
{
	return _end;
}
