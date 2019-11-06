#pragma once

#include "../utils/rect.h"
#include "../utils/draw.h"
#include "container-header.h"

#include "container-style.h"

class Window;

class Container
{
protected:

	/*
	 * Main part
	 */
	Rect _size;
	string _id;
	string _classes;

	Rect _outerSize;


	/*
	 * Parent part
	 */
	Container* _parent;

	/*
	 * Childs part
	 */
	vector<Container*> _childs;
	Rect _sizeChilds;


	/*
	 * Display part
	 */
	bool _display;



	/*
	 * Events part
	 * eventCallback is function< void(Container* sender, Event* e) >
	 */
	map <string, eventCallback> eventListeners;
	/*
	 * @brief Ñallback function for unset event
	 */
	static void unusedCallback(Container* caller, Event* e) {};


	/*
	 * User data part
	 * On this array the user can put a pointer to any information that he may need
	 */
	map <string, void*> _userData;


	/*
	 * State part
	 */
	bool _isHovered;
	bool _isActive;



	/*
	 * SDL part
	 */ 
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Texture* _outerTexture;


	/*
	 * Styles part
	 */
	ContainerStyle _style;
	ContainerStyleRaw _rawStyle;



	/*
	 * Other for Events
	 */
	bool firstMouseMotion;

public:
	Container(string id, Rect size, string classNames);

	/**
	 * Our friends
	 */
public:
	friend Window;



private:
	/*
	 * Event listeners setup
	 */
	void setupEventListeners();


	/*
	 * Helper relationship functions
	 */
	Container* getHoverElement(Point p);
	//Container* getFirstScrollableParent();


	/*
	 * Events
	 */
	void mouseButtonDown(Event* e);
	void mouseButtonUp(Event* e);
	void mouseMotion(Event* e);
	void mouseOut(Event* e);


	/**
	 * @brief Return pointer to container style, for updating in Window::handleStyles;
	 */
	ContainerStyle* styles();

public:
	/*
	 * Setup functions
	 */
	void computeSize();
	void computeChildrenSize();
	void setupChildrenRenderer();

	/*
	 * @brief Function to configure the container and all its childs
	 */
	void setupContainer();




public:
	/*
	 * Render interface
	 */
	void render();


public:
	/*
	 * Relation interface
	 */
	Container* const parent();
	vector <Container*>& childs();

	Container* append(Container* obj);
	Container* appends(vector<Container*> containers);

	bool isChildrenObject(Container* obj);
	bool isParentObject(Container* obj);



public:
	/*
	 * Hover interface
	 */
	bool onHover(Point point);
	Container* const onChildHover(Point point);



public:
	/*
	 * Size interface
	 */
	int width();
	int height();
	int top();
	int left();
	Rect size();
	Rect outerSize();
	
public:
	/*
	 * Event listeners interface
	 */
	void addEventListener(string action, eventCallback callback_function);
	void removeEventListener(string action);
	void callEventListener(string action, Event* e);


public:
	/*
	 * User data interface
	 */
	map <string, void*>& userData();
	void userData(string key, void* data);


public:
	/*
	 * Renderer data interface
	 */
	SDL_Renderer* const renderer();
	SDL_Texture* const texture();


public:
	/*
	 * Display interface
	 */
	Container* show();
	Container* hide();
	Container* toggleDisplay();
	bool display();


public:
	/*
	 * State interface
	 */
	bool isHovered();
	bool isActive();


public:
	/*
	 * Class interface
	 */
	bool hasClass(string className);
	Container* removeClass(string className);
	Container* addClass(string className);
	Container* toggleClass(string className);

};