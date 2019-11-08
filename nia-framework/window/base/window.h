#pragma once

#include "SDL.h"
#include "iostream"

#include "../../utils/rect.h"

#include "../../container/main/MainContainer.h"
#include "../../container/container.h"


#include "..//..//text/text.h"

using std::string;
using std::cout;
using std::endl;

class Window
{
protected:
	map < string, ContainerStyleRaw * > __containersStyles;
	ContainerStyleRaw* addStyle(string className, ContainerStyleRaw* style);
	void handleStyles();

	map <string, Container*> __containers;
	Container* addObject(Container* obj);
	Container* getElementById(string id);
	Containers* getElementsByClassName(string className);

protected:
	Rect size;
	string title;


	SDL_Window* window;
	SDL_Renderer* renderer;


	bool display;

	MainContainer* __container;
	

public:
	Window(string title, Rect size);
	~Window();
	 
public:
	bool init();

	void generalSetup();

	virtual void setup() = 0;
	virtual void update() = 0;

	void show();
	void hide();
	bool isShow();

	void close();

	Rect getSize();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();


	virtual void onEvent(SDL_Event* e) = 0;

private:
	virtual void mouseButtonDown(SDL_Event* e) = 0;
	virtual void mouseButtonUp(SDL_Event* e) = 0;
	virtual void mouseMotion(SDL_Event* e) = 0;
	virtual void mouseWheel(SDL_Event* e) = 0;
	virtual void keyDown(SDL_Event* e) = 0;
	virtual void keyUp(SDL_Event* e) = 0;
	virtual void textInput(SDL_Event* e) = 0;

	/**
	 * Our friends
	 */
public:
	friend Container;

};
