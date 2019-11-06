#pragma once

#include "../object.h"

class Button : public Object
{
private:
	string _text;

public:
	Button(string id, SRect size, SDL_Renderer* renderer, Object* parent, string text);


public:
	virtual void render();

};