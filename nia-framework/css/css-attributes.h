#pragma once

#include "../utils/color.h"

#include "string"
#include "map"

#include "variant"

namespace CSS
{

using std::string;
using std::map;

class css_attribute
{
public:

	static std::variant<int, double, string, Color> get(string attribute, string value);

};

}