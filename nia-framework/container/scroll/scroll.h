#pragma once

#include "SDL.h"
#include "../..//utils/rect.h"

class Container;

class Scroll
{
private:
	Rect _bodySize;
	Rect _sliderSize;

	SDL_Renderer* _renderer;
	SDL_Texture* _texture;

	SDL_Texture* _parentTexture;

	bool _display;


	int _maxValue;
	int _nowValue;

	double _relSizes;

	/* { 0, 1 } */
	double _position;

public:
	Scroll(SDL_Renderer* renderer, Rect size, int maxValue, double relSizes);
	~Scroll();

public:
	friend Container;

private:
	void init();


public:
	void shift(int d);

	bool onHover(Point p);

public:
	void render();

};