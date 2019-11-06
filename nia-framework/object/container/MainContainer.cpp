#include "MainContainer.h"

#include "../..//window/base/window.h"

MainContainer::MainContainer(string id, Rect size, SDL_Renderer* renderer, Window* parent)
	: Container(id, {}, renderer, nullptr)
{
	this->parent_window = parent;
	this->_size = size;
}

void MainContainer::update()
{
	parent_window->update();
}
