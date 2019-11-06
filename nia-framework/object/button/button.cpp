#include "button.h"

Button::Button(string id, SRect size, SDL_Renderer* renderer, Object* parent, string text)
	: Object(id, size, renderer, parent)
{
	this->_text = text;
}

void Button::render()
{
	SDL_SetRenderTarget(_renderer, _texture);

	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xff);
	SDL_RenderFillRect(_renderer, NULL);



	SDL_Texture* parentTexture = nullptr;
	if (_parent != nullptr)
		parentTexture = _parent->texture();
	
	SDL_SetRenderTarget(_renderer, parentTexture);

	SDL_RenderCopy(_renderer, _texture, NULL, &_size.to_rect());

	SDL_SetRenderTarget(_renderer, NULL);
}
