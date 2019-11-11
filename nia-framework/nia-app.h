#pragma once


#include "iostream"
#include "string"
#include "map"

#include "utils/rect.h"

#include "window/main/main-window.h"

using std::string;
using std::cout;
using std::endl;
using std::endl;
using std::map;

class NApp
{
private:
	static NApp* instance;
	NApp();

public:
	static NApp* createApp();


public:
	vector <Window*> windows;

public:
	Window* addWindow(Window* win);


private:
	bool running;
	SDL_Event e;

private:
	bool init();
	void setup();
	void update();
	void onEvent();
	void quit();

public:
	int run();


};
