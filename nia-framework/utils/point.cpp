#include "point.h"
#include "rect.h"

Point::Point() : _x(0), _y(0), isCalculated(true)
{}

Point::Point(int x, int y) : _x(x), _y(y), isCalculated(true)
{}

Point::Point(const Point &obj) noexcept : _x(obj._x), _y(obj._y), top(obj.top), left(obj.left), isCalculated(obj.isCalculated)
{}

Point::Point(SDL_Point p) : _x(p.x), _y(p.y), isCalculated(true)
{}

Point::Point(SDL_Point& p) : _x(p.x), _y(p.y), isCalculated(true)
{}

Point::Point(SDL_Point* p) : _x(p->x), _y(p->y), isCalculated(true)
{}



Point Point::operator+(const Point &obj)
{
	return {this->_x + obj._x, this->_y + obj._y };
}

Point Point::operator-(const Point &obj)
{
	return {this->_x - obj._x, this->_y - obj._y };
}

bool Point::operator==(const Point &obj) const
{
	return this->_x == obj._x && this->_y == obj._y;
}

bool Point::operator!=(const Point &obj) const
{
	return this->_x != obj._x || this->_y != obj._y;
}

Point Point::operator*(int scale)
{
	return {this->_x * scale, this->_y * scale };
}

Point Point::operator*(double scale)
{
	return {(int)(this->_x * scale), (int)(this->_y * scale) };
}

Point Point::operator/(int scale)
{
	return {this->_x / scale, this->_y / scale };
}

Point Point::operator/(double scale)
{
	return {(int)(this->_x / scale), (int)(this->_y / scale) };
}



Point::Point(string top, string left) : top(top), left(left), isCalculated(false)
{}



Point Point::calc(const Rect &parent)
{
	/*if (isCalculated)
		return *this;*/

	this->_x = Utils::parseExpression(top, parent.size._w);
	this->_y = Utils::parseExpression(left, parent.size._h);

	this->isCalculated = true;

	return *this;
}

int Point::x() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Point's 'calc' function." << endl;
		return -1;
	}

	return _x;
}

int Point::y() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Point's 'calc' function." << endl;
		return -1;
	}

	return _y;
}

int Point::x(int v)
{
	_x = v;
	return _x;
}

int Point::y(int v)
{
	_y = v;
	return _y;
}

int Point::dx(int d)
{
	_x += d;
	return _x;
}

int Point::dy(int d)
{
	_y += d;
	return _y;
}

int* Point::px()
{
	return &_x;
}

int* Point::py()
{
	return &_y;
}

SDL_Point Point::toSDLPoint() const
{
	return {_x, _y};
}

bool Point::in(Rect rect, bool ignorePosition) const
{
	SDL_Point p = {_x, _y};
	SDL_Rect r = rect.toSdlRect();

	if (ignorePosition)
	{
		r.x = 0;
		r.y = 0;
	}

	return SDL_PointInRect(&p, &r);
}

bool Point::in(Rect* r, const bool ignorePosition) const
{
	return in(*r, ignorePosition);
}

bool Point::in(SDL_Rect* r) const
{
	SDL_Point p = {_x, _y};
	return SDL_PointInRect(&p, r);
}

bool Point::in(SDL_Rect r) const
{
	return in(&r);
}
