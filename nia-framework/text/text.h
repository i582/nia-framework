#pragma once

#include "../utils/simple-rect.h"
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

enum class TextAlign
{
	LEFT,
	CENTER,
	RIGHT
};

enum class TextBlockVerticalAlign
{
	TOP,
	CENTER,
	BOTTOM
};

class Text
{
private:
	string text;
	vector<string>* words;
	vector<string> lines;

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


	TextAlign textAlign;
	TextBlockVerticalAlign blockVerticalAlign;
	
	int blockMarginTop;
	int blockMarginBottom;
	int blockMarginLeft;
	int blockMarginRight;

	int tw;
	int th;
	SimpleRect textRect;

	int textBlockHeight;

	bool splitted;

	int x;
	int y;

public:
	Text(Container* parent, string text, Rect size, Font* font, size_t fontSize, Color color);
	~Text();

private:
	void init();

	/**
	 * @brief Split text by lines
	 */
	void splitByLines();


	void renderLines();

public:
	void render();

	void setText(string text);
	void setSize(Rect size);
	void setFont(Font* font);
	void setFontSize(size_t fontSize);
	void setColor(Color* color);
	void setLineHeight(double lineHeight);
	void setTextAlign(string align);
	void setTextBlockVerticalAlign(string align);
	void setTextBlockMargin(string side, int value);

	void setRenderer(SDL_Renderer* renderer);
};