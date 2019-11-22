#include "text_line.h"
#include "text.h"

nia::TextLine::TextLine(Text2* parent, string text)
{
	this->parent = parent;
	this->text = text;

	this->isSelect = false;
	this->startCursorSelect;
	this->endCursorSelect;

	setup();
	render();
}

nia::TextLine::~TextLine()
{
	SDL_DestroyTexture(texture);
}

void nia::TextLine::deleteSelected()
{
	this->startCursorSelect = { 0, 0 };
	this->endCursorSelect = { 0, 0 };
}

void nia::TextLine::setup()
{
	// calculate size
	TTF_SizeUTF8(parent->fontTTF, text.c_str(), &size.w, &size.h);
	size.h *= parent->lineHeight;

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTexture(parent->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.w, size.h);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void nia::TextLine::render()
{
	SDL_SetRenderTarget(parent->renderer, texture);
	SDL_SetRenderDrawColor(parent->renderer, 0x33, 0x33, 0x33, 0xff);
	SDL_RenderClear(parent->renderer);


	// рисуем выделение
	SDL_SetRenderDrawColor(parent->renderer, 0x3b, 0x49, 0x47, 0xff);

	SDL_Rect selectedRect = { 0, 0, 0, size.h };

	int startSelect = std::_Min_value(startCursorSelect.x, endCursorSelect.x);
	int endSelect = std::_Max_value(startCursorSelect.x, endCursorSelect.x);

	TTF_SizeUTF8(parent->fontTTF, text.substr(0, startSelect).c_str(), &selectedRect.x, nullptr);
	TTF_SizeUTF8(parent->fontTTF, text.substr(startSelect, abs(startSelect - endSelect)).c_str(), &selectedRect.w, nullptr);

	SDL_RenderFillRect(parent->renderer, &selectedRect);



	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(parent->fontTTF, text.c_str(), parent->colorFont.colorSDL());
	if (textSurface == nullptr)
		return; 
	

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(parent->renderer, textSurface);

	SDL_Rect copyRect = { 0, (parent->fontSize * parent->lineHeight - parent->fontSize) / 2, textSurface->w, textSurface->h };
	SDL_RenderCopy(parent->renderer, textTexture, NULL, &copyRect);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);

	SDL_SetRenderTarget(parent->renderer, parent->texture);
}

void nia::TextLine::setText(string text)
{
	this->text = text;
	setup();
	render();
}

void nia::TextLine::addText(string text, int place)
{
	if (place != this->text.length())
	{
		this->text = this->text.substr(0, place) + text + this->text.substr(place, this->text.length() - place);
	}
	else
	{
		this->text += text;
	}

	
	setup();
	render();
}

bool nia::TextLine::removeSymbol(int place)
{
	if (text.length() > 0)
	{
		if (place == 0)
			return false;

		text = text.substr(0, place - 1) + text.substr(place, text.length() - place);

		setup();
		render();
		return false;
	}
	else
	{
		return true;
	}
}

bool nia::TextLine::removeSymbolAfter(int place)
{
	if (place < text.length())
	{
		text = text.substr(0, place) + text.substr(place + 1, text.length() - place);

		setup();
		render();
		return false;
	}
	else
	{
		return true;
	}
}
