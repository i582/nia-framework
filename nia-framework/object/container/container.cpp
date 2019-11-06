#include "container.h"

Container::Container(string id, Rect size, SDL_Renderer* renderer, Object* parent)
	: Object(id, size, renderer, parent)
{}

Container::Container(string id, Rect size, SDL_Renderer* renderer, string classNames)
	: Object(id, size, renderer, classNames)
{}

Container::Container(string id, Rect size, string classNames)
	: Object(id, size, nullptr, classNames)
{}

Container* Container::create(Container* obj)
{
	return obj;
}


void Container::render()
{
	if (!_display)
		return;

	SDL_SetRenderTarget(_renderer, _texture);

	if (is_hovered)
	{
		if (is_active)
		{
			SDL_SetRenderDrawColor(_renderer, style->activeBackgroundColor() >> 24, (Uint8)(style->activeBackgroundColor() >> 16), (Uint8)(style->activeBackgroundColor() >> 8), (Uint8)(style->activeBackgroundColor()));
		}
		else
		{
			SDL_SetRenderDrawColor(_renderer, style->hoverBackgroundColor() >> 24, (Uint8)(style->hoverBackgroundColor() >> 16), (Uint8)(style->hoverBackgroundColor() >> 8), (Uint8)(style->hoverBackgroundColor()));
		}
	}
	else
	{
		SDL_SetRenderDrawColor(_renderer, style->backgroundColor() >> 24, (Uint8)(style->backgroundColor() >> 16), (Uint8)(style->backgroundColor() >> 8), (Uint8)(style->backgroundColor()));
	}

	SDL_RenderFillRect(_renderer, NULL);


	if (is_hovered)
	{
		if (is_active)
		{
			SDL_SetRenderDrawColor(_renderer, style->activeBorderColor() >> 24, (Uint8)(style->activeBorderColor() >> 16), (Uint8)(style->activeBorderColor() >> 8), (Uint8)(style->activeBorderColor()));
		}
		else
		{
			SDL_SetRenderDrawColor(_renderer, style->hoverBorderColor() >> 24, (Uint8)(style->hoverBorderColor() >> 16), (Uint8)(style->hoverBorderColor() >> 8), (Uint8)(style->hoverBorderColor()));
		}
	}
	else
	{
		SDL_SetRenderDrawColor(_renderer, style->borderColor() >> 24, (Uint8)(style->borderColor() >> 16), (Uint8)(style->borderColor() >> 8), (Uint8)(style->borderColor()));
	}

	SDL_RenderDrawRect(_renderer, NULL);

	

	for (auto& child : _childrens)
	{
		child->render();
	}

	//aalineColor(_renderer, 0, 0, 10, 10, 0x00000000);
	renderScrollY();
	

	SDL_Texture* parentTexture = nullptr;
	if (_parent != nullptr)
	{
		parentTexture = _parent->texture();
	}
		
	SDL_SetRenderTarget(_renderer, parentTexture);

	// src part textures
	Rect _sizeCopy = _size;

	Rect src = _sizeCopy;
	src.start._x = 0; src.y = scrollY_Val;

	SDL_RenderCopy(_renderer, _texture, &src.toSDLRect(), &_sizeCopy.toSDLRect());


	//SDL_SetRenderTarget(_renderer, NULL);
}
