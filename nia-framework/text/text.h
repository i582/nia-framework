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

class Text
{
private:
	string text;
	vector<string>* words;

	Rect size;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	Font font;
	size_t fontSize;
	TTF_Font* ttf_font;
	Color color;


	double lineHeight;

	int x;
	int y;

public:
	Text(SDL_Renderer* renderer, string text, Rect size, Font& font, size_t fontSize, Color& color);
	~Text();

private:
	void init();

	/**
	 * @brief Rendering a single word with a hyphenation if a word does not fit into the line
	 */
	void renderWord(string word);

public:
	void render();

};