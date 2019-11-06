#include "text.h"

Text::Text(SDL_Renderer* renderer, string text, Rect size, Font& font, size_t fontSize, Color& color)
{
	this->renderer = renderer;
	this->texture = nullptr;
	this->text = text;
	this->size = size;
	this->font = font;
	this->fontSize = fontSize;
	this->ttf_font = font(fontSize);
	this->color = color;

	this->lineHeight = 1.3;

	this->x = 0;
	this->y = 0;

	init();
	render();
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

	Color back("#000000");

	SDL_SetRenderTarget(renderer, texture);
	
	SDL_SetRenderDrawColor(renderer, back.r(), back.g(), back.b(), back.a());
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, NULL);



	Point p;
	TTF_SizeUTF8(ttf_font, text.c_str(), p.px(), p.py());


	

	for (auto& word : *words)
	{
		renderWord(word + ' ');
	}


	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, texture, NULL, &size.toSdlRect());
}
