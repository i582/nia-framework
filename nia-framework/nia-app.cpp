#include "nia-app.h"

NApp* NApp::instance = nullptr;


NApp* NApp::createApp()
{
	if (instance == nullptr)
		instance = new NApp;

	return instance;
}

Window* NApp::addWindow(Window* win)
{
	windows.push_back(win);

	update();

	return windows.back();
}

NApp::NApp()
{
	this->windows = {};
	this->running = true;
	
	this->init();

	setlocale(LC_ALL, "ru_RU.UTF-8");
	setlocale(LC_NUMERIC, "eng");
}



bool NApp::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
		return false;
	}


	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	return true;
}

void NApp::setup()
{
	
}

void NApp::update()
{
	for (auto& window : windows)
	{
		window->update();
	}
}

void NApp::onEvent()
{
	int windowId = -1;
	SDL_StartTextInput();
	while (running && SDL_WaitEvent(&e))
	{
		windowId = e.window.windowID - 1;

		if (windowId < windows.size())
			windows[windowId]->onEvent(&e);
	}
	SDL_StopTextInput();
}

void NApp::quit()
{
	running = false;
}

int NApp::run()
{
	setup();
	update();
	onEvent();

	return 0;
}

