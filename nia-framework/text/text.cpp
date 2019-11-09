#include "text.h"
#include "..//container/container.h"

Text::Text(Container* parent, string text, Rect size, Font* font, size_t fontSize, Color color)
{
	this->parent = parent;
	this->renderer = parent->renderer();
	this->texture = nullptr;
	this->text = text;
	this->size = size;
	this->font = font;
	this->fontSize = fontSize;

	if (font != nullptr)
		this->ttf_font = font->at(fontSize);

	this->color = color;

	this->lineHeight = 1.3;

	this->x = 0;
	this->y = 0;

	this->needReRender = true;

	init();
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
}

void Text::init()
{
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.w(), size.h());
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	words = Utils::split(text, ' ');
}

void Text::renderWord(string word)
{
	Point p;
	TTF_SizeUTF8(ttf_font, word.c_str(), p.px(), p.py());
	
	if (x + p.x() > size.w())
	{
		x = 0;
		y += p.y() + (lineHeight * fontSize - fontSize);
	}

	Rect textRect;
	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(ttf_font, word.c_str(), color.colorSDL());

	textRect.x(x);
	textRect.y(y);
	textRect.w(textSurface->w);
	textRect.h(textSurface->h);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_SetTextureBlendMode(textTexture, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(textSurface);

	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect.toSdlRect());
	SDL_DestroyTexture(textTexture);

	
	x += p.x();
}

void Text::render()
{
	this->x = 0;
	this->y = 0;

	
	if (needReRender)
	{
		SDL_SetRenderTarget(renderer, texture);

		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0x00);
		SDL_RenderClear(renderer);

		for (auto& word : *words)
		{
			renderWord(word + ' ');
		}

		this->needReRender = false;
	}


	SDL_SetRenderTarget(renderer, parent->texture());
	SDL_RenderCopy(renderer, texture, NULL, &size.toSdlRect());
}

void Text::setText(string text)
{
	if (this->text == text)
		return;

	this->text = text;
	this->words = Utils::split(text, ' ');

	this->needReRender = true;
}

void Text::setSize(Rect size)
{
	if (this->size == size)
		return;

	this->size = size;

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.w(), size.h());
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	this->needReRender = true;
}

void Text::setFont(Font* font)
{
	if (this->font == font)
		return;

	this->font = font;

	if (this->font != nullptr)
		this->ttf_font = font->at(fontSize);

	this->needReRender = true;
}

void Text::setFontSize(size_t fontSize)
{
	if (this->fontSize == fontSize)
		return;

	this->fontSize = fontSize;

	if (this->font != nullptr)
		this->ttf_font = font->at(fontSize);

	this->needReRender = true;
}

void Text::setColor(Color color)
{
	if (this->color == color)
		return;

	this->color = color;

	this->needReRender = true;
}

void Text::setLineHeight(double lineHeight)
{
	if (this->lineHeight == lineHeight)
		return;

	this->lineHeight = lineHeight;

	this->needReRender = true;
}

void Text::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}
