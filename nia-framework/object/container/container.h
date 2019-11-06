#pragma once

#include "../object.h"

#include "SDL2_gfxPrimitives.h"


class Container : public Object
{
private:


public:
	Container(string id, Rect size, SDL_Renderer* renderer, Object* parent = nullptr);
	Container(string id, Rect size, SDL_Renderer* renderer, string classNames);
	Container(string id, Rect size, string classNames = "");


	static Container* create(Container* obj);

public:
	virtual void render();

};