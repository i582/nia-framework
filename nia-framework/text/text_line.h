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

class Text;

class TextLine
{
private:
	string text;

	SimpleRect size;

	Text* parent;

	SDL_Renderer* renderer;
	SDL_Texture* parentTexture;

	SDL_Texture* texture;

	Font* font;
	size_t fontSize;
	TTF_Font* fontTTF;
	Color color;

public:
	TextLine(Text* parent, string text, int x, int y);


public:


};