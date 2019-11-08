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


	size_t _maxValue;
	size_t _nowValue;

	double _relSizes;

	/* { 0, 1 } */
	double _position;

public:
	Scroll(SDL_Renderer* renderer, Rect size, size_t maxValue, double relSizes);
	~Scroll();

public:
	friend Container;

private:
	void init();


public:
	void shift(int d);

public:
	void render();

};