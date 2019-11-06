#include "rect.h"

Rect::Rect(): isCalculated(true)
{}

Rect::Rect(const Point start, const Size size)
{
	this->size = size;
	this->start = start;

	this->isCalculated = size.isCalculated || start.isCalculated;
}

Rect::Rect(int x, int y, int w, int h)
{
	this->size = { w, h };
	this->start = { x, y };

	this->isCalculated = size.isCalculated || start.isCalculated;
}

int Rect::w() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Rect's 'calc' function." << endl;
		return -1;
	}

	return size._w;
}

int Rect::h() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Rect's 'calc' function." << endl;
		return -1;
	}

	return size._h;
}

int Rect::x(int v)
{
	start._x = v;
	return start._x;
}

int Rect::y(int v)
{
	start._y = v;
	return start._y;
}

int Rect::w(int v)
{
	size._w = v;
	return size._w;
}

int Rect::h(int v)
{
	size._h = v;
	return size._h;
}

int Rect::y() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Rect's 'calc' function." << endl;
		return -1;
	}

	return start._y;
}

int Rect::x() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Rect's 'calc' function." << endl;
		return -1;
	}

	return start._x;
}

Rect Rect::calc(const Rect& parent)
{
	if (!start.isCalculated)
		start.calc(parent);

	if (!size.isCalculated)
		size.calc(parent);

	this->isCalculated = true;

	return *this;
}

SDL_Rect Rect::toSdlRect() const
{
	return {start._x, start._y, size._w, size._h};
}
