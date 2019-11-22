#pragma once

#include <string>
#include <vector>
#include <SDL.h>

#include "../utils/simple-size.h"
#include "../font/font.h"
#include "../utils/color.h"

namespace nia
{

using std::string;
using std::vector;

struct Word
{
	string text;
	Color color;

	Word(string text, Color color) : text(text), color(color) {};
};

}