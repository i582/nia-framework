#pragma once

#include "../base/window.h"

#include "../../utils/utils.h"

class MainWindow : public Window
{
private:


public:
	MainWindow(string title, Rect size) : Window(title, size) { setup(); };

public:
	virtual void setup();
	virtual void update();


	virtual void onEvent(SDL_Event* e);

private:
	// events
	virtual void mouseButtonDown(SDL_Event* e);
	virtual void mouseButtonUp(SDL_Event* e);
	virtual void mouseMotion(SDL_Event* e);
	virtual void mouseWheel(SDL_Event* e);
	virtual void keyDown(SDL_Event* e);
	virtual void keyUp(SDL_Event* e);
	virtual void textInput(SDL_Event* e);
};