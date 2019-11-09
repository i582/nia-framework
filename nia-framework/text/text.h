#pragma once

#include "../utils/rect.h"
#include "../utils/color.h"
#include "../font/fonts.h"
#include "iostream"
#include "string"
#include "map"

using std::map;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

class Container;

class Text
{
private:
	string text;
	vector<string>* words;

	Rect size;
	Container* parent;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	Font* font;
	size_t fontSize;
	TTF_Font* ttf_font;
	Color color;

	bool needReRender;

	double lineHeight;

	int x;
	int y;

public:
	Text(Container* parent, string text, Rect size, Font* font, size_t fontSize, Color color);
	~Text();

private:
	void init();

	/**
	 * @brief Rendering a single word with a hyphenation if a word does not fit into the line
	 */
	void renderWord(string word);

public:
	void render();

	void setText(string text);
	void setSize(Rect size);
	void setFont(Font* font);
	void setFontSize(size_t fontSize);
	void setColor(Color color);
	void setLineHeight(double lineHeight);

	void setRenderer(SDL_Renderer* renderer);
};