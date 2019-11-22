#pragma once
#include <string>
#include <SDL.h>

#include "../utils/simple-size.h"
#include "../font/font.h"
#include "../utils/color.h"

namespace nia
{

struct CursorPosition
{
	int x, y;

	CursorPosition() : x(0), y(0) {}
	CursorPosition(int x, int y) : x(x), y(y) {}
};

using std::string;

class Text2;

class TextLine
{
private:
	size_t id;
	string text;
	SimpleSize size;
	
	const Text2* parent;

	SDL_Texture* texture;

	bool isSelect;
	CursorPosition startCursorSelect;
	CursorPosition endCursorSelect;

public:
	TextLine(Text2* parent, string text);
	~TextLine();

public:
	friend Text2;

private:
	void deleteSelected();

private:
	void setup();
	void render();

public:
	void setText(string text);
	void addText(string text, int place);
	bool removeSymbol(int place);
	bool removeSymbolAfter(int place);
};




}