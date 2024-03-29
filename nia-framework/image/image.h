#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "iostream"
#include "string"

#include "../utils/simple-rect.h"
#include "../utils/simple-point.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;

class Container;

class Image
{
private:
	string path;
	SimpleRect textureSize;
	SimpleRect generalSize;
	SimpleRect containerSize;


	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Texture* parentTexture;

	Container* parent;

	bool needReRender;

public:
	Image(Container* parent);
	
public:
	void setPath(string path);
	void setRenderer(SDL_Renderer* renderer);

	void setImageSize(SimpleRect generalSize);

	void setImageShift(SimplePoint p);
	
	void setImageSizeW(string size);

private:
	SDL_Texture* createTexture();

public:
	void render();

};