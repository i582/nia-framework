#include "nia-app.h"

NApp* NApp::instance = nullptr;


NApp* NApp::createApp()
{
	if (instance == nullptr)
		instance = new NApp;

	return instance;
}

Window* NApp::addWindow(string title, Rect size, string id)
{
	windows.push_back(new MainWindow(title, size));

	update();

	return windows.back();
}

NApp::NApp()
{
	this->windows = {};
	this->running = true;
	
	this->init();

	setlocale(LC_ALL, "Rus");
	setlocale(LC_NUMERIC, "eng");
}



bool NApp::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
		return false;
	}

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
	while (running && SDL_WaitEvent(&e))
	{
		windowId = e.window.windowID - 1;

		if (windowId < windows.size())
			windows[windowId]->onEvent(&e);
	}
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

