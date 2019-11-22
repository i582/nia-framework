#pragma once
#include <vector>

#include "text_line.h"
#include "../utils/simple-rect.h"
#include "../utils/simple-point.h"
#include "../utils/utils.h"

#include "ctime"

namespace nia
{

using std::vector;

class Text2
{
private:
	vector<TextLine*> lines;
	string text;

	SimpleRect size;

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Font* font;
	size_t fontSize;
	TTF_Font* fontTTF;
	Color colorFont;

	double lineHeight;

	CursorPosition cursorPos;

	bool isSelected;
	CursorPosition startCursorSelect;
	CursorPosition endCursorSelect;

	bool mousePush;

public:
	Text2(SDL_Renderer* renderer, string text, SimpleRect size, Font* font, size_t fontSize, Color colorFont);
	~Text2();

public:
	friend TextLine;

private:
	void splitByLines();
	void setup();

	void splitLinesByToken();

	void renderCursor();

	void handleSelect();
	void deleteSelect();

	CursorPosition whereIsCursor(SimplePoint p);

	string copySelect();

public:
	void render();
	
	void mouseMotion(SDL_Event* e);
	void mouseButtonUp(SDL_Event* e);
	void mouseButtonDown(SDL_Event* e);
	void keyDown(SDL_Event* e);
	void textInput(SDL_Event* e);

};



}