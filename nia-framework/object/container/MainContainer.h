#pragma once

#include "container.h"

class MainContainer : public Container
{
private:
	Window* parent_window;

public:
	MainContainer(string id, Rect size, SDL_Renderer* renderer, Window* parent);

public:
	void update();

};