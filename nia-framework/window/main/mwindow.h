#pragma once

#include "main-window.h"

class MWindow : public MainWindow
{
public:
	nia::Text2* text;

public:
	MWindow(string title, Rect size) : MainWindow(title, size) { setup(); };

public:
	virtual void setup();

};