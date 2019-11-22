#include "MainContainer.h"
#include "../../window/base/window.h"

MainContainer::MainContainer(Window* parent)
	: Container("$$main$$", {0, 0, parent->getSize().w(), parent->getSize().h() }, "main")
{
	this->_window = parent;
	this->_renderer = parent->getRenderer();
}

void MainContainer::update()
{
	if (_window != nullptr)
	{
		_window->update();
	}
}

void MainContainer::setupSize(Rect* size)
{
	this->_innerSize = _outerSize = *size;
	this->computeSize();
	this->computeChildrenSize();
	this->render();
}
