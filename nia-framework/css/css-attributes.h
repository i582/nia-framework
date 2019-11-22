#pragma once

#define _DEBUG_VERSION_NO

#include "../utils/color.h"
#include "iostream"
#include "vector"
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