#pragma once

#include "SDL.h"

#include "size.h"
#include "point.h"
#include "utils.h"

#include "iostream"
#include "string"

using std::string;
using std::cout;
using std::endl;


class Rect
{

/**
 * @brief Part for normal rect
 */
public:
	Size size;
	Point start;

public:
	Rect();
	Rect(Point start, Size size);
	Rect(int x, int y, int w, int h);
	Rect(string left, string top, string width, string height);
	
	bool operator==(const Rect& obj);
/**
 * @brief Part for where definition from a string, like 100px or 24%
 */
private:
	bool isCalculated;

public:
	/**
	 * @brief General function calculating sizes from strings
	 * @param parent Rect relative to which values ​​containing percentages are calculated
	 * @return Rectangle with calculated values
	 */
	Rect calc(const Rect& parent);


/**
 * @brief Our friends
 */
public:
	friend Point;
	friend Size;

/**
 * @brief general interface
 */
public:
	/**
	 * @brief Getters for comfortable use
	 * @return Value from function name or -1 if strings are not calculated
	 */
	int x() const;
	int y() const;
	int w() const;
	int h() const;

	/**
	 * @brief Setters for comfortable use
	 * @return New value from function name
	 */
	int x(int v);
	int y(int v);
	int w(int v);
	int h(int v);

	int dx(int d);
	int dy(int d);
	int dw(int d);
	int dh(int d);

public:
	/**
	 * @brief return a rectangle in the format understood by SDL API
	 * @return Rect struct understood by SDL API
	 */
	SDL_Rect toSdlRect() const;
};

