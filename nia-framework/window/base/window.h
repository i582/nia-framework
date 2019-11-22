#pragma once

#include "SDL.h"
#include "iostream"

#include "../../utils/rect.h"

#include "../../container/main/MainContainer.h"
#include "../../container/container.h"

#include "..//..//css/css.h"

#include "..//..//text/text.h"
#include "..//..//text2/text.h"

using std::string;
using std::cout;
using std::endl;



class Window
{
public:
	static Container* create(Container* ptr);


protected:
	map <string, CSS::css_block> __containersStyles;
	CSS::css_block* addStyle(string className, CSS::css_block style);
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
	MainContainer* $$;

public:
	Window(string title, Rect size);
	~Window();
	 
private:
	bool init();

	void generalSetup();

	virtual void setup() = 0;

public:
	virtual void update() = 0;
	virtual void onEvent(SDL_Event* e) = 0;

	void show();
	void hide();
	bool isShow();

	void close();

	Rect getSize();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

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


protected:
	bool wasSetupContainer;
	bool wasSetupStyle;


protected:


	CSS::css main_css;

	/**
	 *  @brief Function for include css style file
	 */
	void include(string path);

};