#pragma once

#include "color.h"
#include "utils.h"

#include "vector"

using std::vector;

class Shadow
{
private:
	string shadowString;

	size_t _thickness;
	size_t _blur;

	Color _start;
	Color _end;

public:
	Shadow();
	Shadow(string shadowString);

private:
	void init();

public:
	size_t thickness();
	size_t blur();

	size_t outerSize();

	Color startColor();
	Color endColor();


};