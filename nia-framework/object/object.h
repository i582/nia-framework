#pragma once

#include "SDL.h"
#include "string"
#include "vector"
#include "map"

#include "functional"

#include "../utils/rect.h"

#include "objects.h"

using namespace std;


using color = Uint32;


class ObjectStyle
{
private:
	color _backgroundColor;
	color _textColor;
	color _hoverBackgroundColor;
	color _activeBackgroundColor;

	color _borderColor;
	color _hoverBorderColor;
	color _activeBorderColor;

	SDL_Cursor* _cursor;
	SDL_Cursor* _hoverCursor;

public:
	ObjectStyle();
	~ObjectStyle();

public:
	color backgroundColor();
	color textColor();
	color hoverBackgroundColor();

	SDL_Cursor* cursor();
	ObjectStyle* cursor(string cursor_id);

	SDL_Cursor* hoverCursor();
	ObjectStyle* hoverCursor(string cursor_id);

	ObjectStyle* backgroundColor(color newColor);
	ObjectStyle* textColor(color newColor);
	ObjectStyle* hoverBackgroundColor(color newColor);

	color activeBackgroundColor();
	ObjectStyle* activeBackgroundColor(color newColor);


	color borderColor();
	color hoverBorderColor();
	color activeBorderColor();

	ObjectStyle* borderColor(color newColor);
	ObjectStyle* hoverBorderColor(color newColor);
	ObjectStyle* activeBorderColor(color newColor);
};


class Window;

class Object
{
protected:
	Rect _size;
	string _id;
	Object* _parent;


	vector <Object*> _childrens;
	Rect _sizeChildrens;

	SDL_Texture* _texture;
	SDL_Renderer* _renderer;


	string classes;

	map <string, callback> eventListeners;


	bool _display;

public:
	Object(string id, Rect size, SDL_Renderer* renderer, Object* parent);
	Object(string id, Rect size, SDL_Renderer* renderer, string classNames);
	Object(string id, Rect size, string classNames);

private:
	void setupEventListeners();
	static void unusedCallback(Object* caller, SDL_Event* e) {};

	bool firstMouseMotion;
	void resetFirstMouseMotion();

public:
	SDL_Texture* texture();

public:
	friend Window;

public:
	void computeSize();
	void computeChildrenSize();
	void setupChildrenRenderer();


	void setupContainer();

protected:
	// scroll part

	/* { 0, 1 } */
	double scrollY_Pos;
	int scrollY_Val;
	int scrollY_Delta;


	bool scrollY_Visible;

	int scrollY_Width;
	int scrollY_Height;

	bool scrollY_Active;

	int scrollY_SliderWidth;
	int scrollY_SliderHeight;

public:
	void renderScrollY();

public:
	Object* const parent();
	vector <Object*>* const childrens();

	int width();
	int height();
	int top();
	int left();
	Rect size();
	 
	ObjectStyle* styles();
	ObjectStyle* styles(ObjectStyle* newStyle);

	Object* show();
	Object* hide();
	Object* toggleDisplay();
	bool display();

	Object* append(Object* obj);

	Object* appendSomeObjects(vector<Object*> someObjects);



	bool onHover(Point point);
	Object* const onChildHover(Point point);
	bool isChildrenObject(Object* obj);
	bool isParentObject(Object* obj);


	void addEventListener(string action, callback callback_function);


	Object* getHoverElement(SDL_Event* e);
	Object* getFirstScrollableParent();

	void mouseButtonDown(SDL_Event* e);
	void mouseButtonUp(SDL_Event* e);
	void mouseMotion(SDL_Event* e);
	void mouseOut(SDL_Event* e);

	void mouseScroll(SDL_Event* e, int direction);

	SDL_Renderer* renderer();

	virtual void render() = 0;
	virtual void update() {};


protected:
	static Object* hoverObject;
	bool is_hovered;

	bool is_active;

protected:
	ObjectStyle* style;

	
public:
	map <string, string> dataUser;


	// classes part
public:
	bool hasClass(string className);
	Object* removeClass(string className);
	Object* addClass(string className);
	Object* toggleClass(string className);
};




#define START_CHILDS ->appendSomeObjects({
#define END_CHILDS })
#define NEXT_CHILD ,