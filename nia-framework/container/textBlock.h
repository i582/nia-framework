#pragma once

#include "container.h"

class TextBlock : public Container
{
private:

	
public:
	TextBlock(string id, Rect size, string classNames) : Container(id, size, classNames) { this->setup(); };

public:
	void setup();

};