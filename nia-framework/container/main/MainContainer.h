#pragma once

#include "../container.h"
#include "string"

using std::string;
using std::to_string;

class Window;

class MainContainer : public Container
{
private:
	Window* parent;

public:
	MainContainer(Window* parent);

public:
	void update();

};