#include "MainContainer.h"
#include "../../window/base/window.h"

MainContainer::MainContainer(Window* parent)
	: Container("main", {0, 0, parent->getSize().w(), parent->getSize().h() }, "")
{
	this->parent = parent;
	this->_renderer = parent->getRenderer();
}

void MainContainer::update()
{
	if (parent != nullptr)
	{
		parent->update();
	}
}
