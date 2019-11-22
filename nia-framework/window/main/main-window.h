#pragma once

#include "../base/window.h"

#include "../../utils/utils.h"

class MainWindow : public Window
{
public:
	nia::Text2* text;

public:
	MainWindow(string title, Rect size);


public:
	virtual void setup() = 0;

private:
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