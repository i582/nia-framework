#pragma once

#include "main-window.h"

class MWindow : public MainWindow
{
public:
	MWindow(string title, Rect size) : MainWindow(title, size) { setup(); };

public:
	virtual void setup();

};