#pragma once

#include "SDL.h"
#include "string"
#include "vector"
#include "map"
#include "functional"

using std::vector;
using std::function;
using std::map;
using Event = SDL_Event;

class Container;
using eventCallback = function< void(Container* sender, Event* e) >;
using eachCallback = function< void(Container* sender) >;

#define lambda [=]