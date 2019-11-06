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
	static map < string, ContainerStyleRaw * > __containersStyles;
	static ContainerStyleRaw* addStyle(string className, ContainerStyleRaw* style);
	static void handleStyles();

	static map <string, Container*> __containers;
	static Container* addObject(Container* obj);
	static Container* getElementById(string id);
	//static Containers* getElementsByClassName(string className);

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

	virtual void setup() {};
	virtual void update() {};

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

	// object
	//Object* addObject(Object* obj);

};
