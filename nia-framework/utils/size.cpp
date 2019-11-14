#include "size.h"
#include "rect.h"

Size::Size() : _w(0), _h(0), isCalculated(true)
{}

Size::Size(int w, int h) : _w(w), _h(h), isCalculated(true)
{}

Size::Size(const Size &obj) noexcept : _w(obj._w), _h(obj._h), width(obj.width), height(obj.height), isCalculated(obj.isCalculated)
{}

Size Size::operator+(const Size &obj)
{
	Size size;
	size._w = this->_w + obj._w;
	size._h = this->_h + obj._h;
	return size;
}

Size Size::operator-(const Size &obj)
{
	Size size;
	size._w = this->_w - obj._w;
	size._h = this->_h - obj._h;
	return size;
}

bool Size::operator==(const Size &obj) const
{
	return this->_w == obj._w && this->_h == obj._h;
}

bool Size::operator!=(const Size &obj) const
{
	return this->_w != obj._w || this->_h != obj._h;
}

Size Size::operator*(int scale)
{
	Size size;
	size._w = this->_w * scale;
	size._h = this->_h * scale;
	return size;
}

Size Size::operator*(double scale)
{
	Size size;
	size._w = (int)(this->_w * scale);
	size._h = (int)(this->_h * scale);
	return size;
}

Size Size::operator/(int scale)
{
	Size size;
	size._w = this->_w / scale;
	size._h = this->_h / scale;
	return size;
}

Size Size::operator/(double scale)
{
	Size size;
	size._w = (int)(this->_w / scale);
	size._h = (int)(this->_h / scale);
	return size;
}







Size::Size(string width, string height) : width(width), height(height), isCalculated(false)
{

}

Size Size::calc(const Rect& parent)
{
	/*if (isCalculated)
		return *this;*/

	this->_w = Utils::parseExpression(width, parent.size._w);
	this->_h = Utils::parseExpression(height, parent.size._h);

	this->isCalculated = true;

	return *this;
}

int Size::w() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Size's 'calc' function." << endl;
		return -1;
	}

	return _w;
}

int Size::h() const
{
	if (!isCalculated)
	{
		cout << "Error: String were not parsed into values. See Size's 'calc' function." << endl;
		return -1;
	}

	return _h;
}

int Size::w(int v) 
{
	_w = v;
	return _w;
}

int Size::h(int v)
{
	_h = v;
	return _h;
}

int Size::dw(int d)
{
	_w += d;
	return _w;
}

int Size::dh(int d)
{
	_h += d;
	return _h;
}