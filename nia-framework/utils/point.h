#pragma once

#include "SDL.h"

#include "iostream"
#include "string"

#include "size.h"
#include "utils.h"

using std::string;
using std::cout;
using std::endl;

class Rect;

class Point
{

/**
 * @brief Part for numerical size
 */
private:
	int _x, _y;

public:
	Point();
	Point(int x, int y);
	Point(const Point& obj) noexcept;

	explicit Point(SDL_Point p);
	explicit Point(SDL_Point& p);
	explicit Point(SDL_Point* p);

	Point operator+(const Point &obj);
	Point operator-(const Point &obj);
	Point operator*(int scale);
	Point operator*(double scale);
	Point operator/(int scale);
	Point operator/(double scale);

	bool operator==(const Point &obj) const;
	bool operator!=(const Point &obj) const;


/**
 * @brief Part for where definition from a string, like 100px or 24%
 */
public:
	/**
	 * @brief Strings must contain px or %
	 */
	string top, left;

	bool isCalculated;

public:
	Point(string top, string left);

	/**
	 * @brief Function calculating sizes from strings
	 * @param parent Size relative to which values ​​containing percentages are calculated
	 * @return Rectangle with calculated values
	 */
	Point calc(const Rect& parent);


public:
	friend Rect;
/**
 * @brief general interface
 */
public:
	int x() const;
	int y() const;
	int x(int v);
	int y(int v);

	int dx(int d);
	int dy(int d);

	int* px();
	int* py();

	/**
	 * @brief
	 * @return Point struct understood by SDL API
	 */
	SDL_Point toSDLPoint() const;

	/**
	 * @brief Checks if a given point lies in a rectangle
	 * @param r Rect or SDL_Rect
	 * @param ignorePosition flag meaning not taking into account the position of the rectangle
	 * @return [true|false]
	 */
	bool in(Rect, bool ignorePosition = false) const;
	bool in(Rect* r, bool ignorePosition = false) const;

	bool in(SDL_Rect r) const;
	bool in(SDL_Rect* r) const;
};









