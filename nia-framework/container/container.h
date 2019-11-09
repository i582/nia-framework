#pragma once

#include "../utils/rect.h"
#include "../utils/draw.h"
#include "../text/text.h"

#include "../../container/scroll/scroll.h"

#include "containers/containers.h"

#include "container-header.h"

#include "style/styles.h"


class Window;

class Container
{
public:
	static Container* hoverContainer;

protected:

	/**
	 * Main part
	 */
	Rect _innerSize;
	string _id;
	string _classes;

	Rect _outerSize;


	/**
	 * Parent part
	 */
	Container* _parent;
	Window* _window;


	/**
	 * Childs part
	 */
	vector<Container*> _childs;
	Rect _sizeChilds;


	/**
	 * Display part
	 */
	bool _display;



	/**
	 * Events part
	 * eventCallback is function< void(Container* sender, Event* e) >
	 */
	map <string, eventCallback> eventListeners;
	/**
	 * @brief Ñallback function for unset event
	 */
	static void unusedCallback(Container* caller, Event* e) {};


	/**
	 * User data part
	 * On this array the user can put a pointer to any information that he may need
	 */
	map <string, void*> _userData;


	/**
	 * State part
	 */
	bool _isHovered;
	bool _isActive;


	
	/**
	 * SDL part
	 */ 
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Texture* _outerTexture;


	/**
	 * Styles part
	 */
	Styles _style;

	/**
	 * Scroll part
	 */
	Scroll* scroll;
	bool scrollable;

	/**
	 * Other for Events
	 */
	bool firstMouseMotion;


	/**
	 * Text part
	 */
	Font* _font;
	Text* _text;


public:
	Container(string id, Rect size, string classNames);
	~Container();

	/**
	 * Our friends
	 */
public:
	friend Window;



private:
	/**
	 * Event listeners setup
	 */
	void setupEventListeners();


public:
	/**
	 * Helper relationship functions
	 */
	Container* getHoverElement(Point p);
	Container* getFirstScrollableParent();


public:
	/**
	 * Events
	 */
	void mouseButtonDown(Event* e);
	void mouseButtonUp(Event* e);
	void mouseMotion(Event* e);
	void mouseOut(Event* e);
	void mouseScroll(Event* e, int scrollDirection);

	/**
	 * @brief Return pointer to container style, for updating in Window::handleStyles;
	 */
	Styles* styles();

public:
	/**
	 * Setup functions
	 */
	void computeSize();
	void computeChildrenSize();
	void setupChildrenRenderer();
	

	/**
	 * @brief Function to configure the container and all its childs
	 */
	void setupContainer();




public:
	/**
	 * Render interface
	 */
	void render();


public:
	/**
	 * Relation interface
	 */
	Container* const parent();
	vector <Container*>& childs();

	Window* window();

	Container* append(Container* obj);
	Container* appends(vector<Container*> containers);

	bool isChildrenObject(Container* obj);
	bool isParentObject(Container* obj);



public:
	/**
	 * Hover interface
	 */
	bool onHover(Point point);
	Container* const onContainerHover(Point point);


public:
	/**
	 * Size interface
	 */
	int width();
	int height();
	int top();
	int left();
	Rect size();
	Rect outerSize();
	

	/**
	 * id interface
	 */
	string id();

public:
	/**
	 * Event listeners interface
	 */
	void addEventListener(string action, eventCallback callback_function);
	void removeEventListener(string action);
	void callEventListener(string action, Event* e);


public:
	/**
	 * User data interface
	 */
	map <string, void*>& userData();
	void addUserData(string key, void* data);
	void* userData(string key);

public:
	/**
	 * Renderer data interface
	 */
	SDL_Renderer* const renderer();
	SDL_Texture* const texture();


public:
	/**
	 * Scroll interface
	 */
	bool isScrollable();

public:
	/**
	 * Display interface
	 */
	Container* show();
	Container* hide();
	Container* toggleDisplay();
	bool display();


public:
	/**
	 * State interface
	 */
	bool isHovered();
	bool isActive();


public:
	/**
	 * Class interface
	 */
	bool hasClass(string className);
	Container* removeClass(string className);
	Container* addClass(string className);
	Container* toggleClass(string className);


public:
	Text* text();
};

