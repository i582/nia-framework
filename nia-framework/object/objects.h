#pragma once

#include "SDL.h"
#include "string"
#include "vector"
#include "map"
#include "functional"



using namespace std;

class Object;

using callback = function< void(Object* caller, SDL_Event* e) >;

using callbackEach = function< void(Object* caller) >;

class Objects
{
private:
	vector <Object*>* objects;

public:
	Objects(vector <Object*>* objects);
	~Objects();

public:
	void addEventListener(string action, callback callback_function);
	void each(callbackEach callback_function);
};