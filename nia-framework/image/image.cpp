#include "image.h"
#include "../container/container.h"

Image::Image(Container* parent)
{
	if (parent == nullptr)
		return;

	IMG_Init(IMG_INIT_PNG);

	this->renderer = parent->renderer();
	this->parentTexture = parent->texture();

	this->containerSize = this->generalSize = { 0, 0 , parent->width(), parent->height() } ;
}

void Image::setPath(string path)
{
	this->path = path;
}

void Image::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Image::setImageSize(SimpleRect generalSize)
{
	this->generalSize = generalSize;
}

void Image::setImageShift(SimplePoint p)
{
	this->generalSize.x = p.x;
	this->generalSize.y = p.y;
}

SDL_Texture* Image::createTexture()
{
	if (this->path.empty())
		return nullptr;

	this->texture = IMG_LoadTexture(renderer, this->path.c_str());

	if (this->texture == nullptr)
	{
		cout << "Error: " << IMG_GetError() << endl;
		return nullptr;
	}

	SDL_QueryTexture(this->texture, nullptr, nullptr, &textureSize.w, &textureSize.h);

	return this->texture;
}

void Image::render()
{
	if (texture == nullptr)
		texture = createTexture();

	SDL_SetRenderTarget(renderer, this->parentTexture);

	SimpleRect srcRect = { 0, 0, generalSize.w, generalSize.h };
	
	SDL_RenderCopy(renderer, this->texture, NULL, &generalSize.toSdlRect());
}
