#pragma once

#include "../..//utils/color.h"

#include "string"
#include "map"

using std::string;
using std::map;


class StyleState
{
private:
	map <string, string> colors;
	map <string, string> text;

public:
	StyleState();
	StyleState(bool generalSetup);

public:
	StyleState* setColor(string type, string value);
	StyleState* setTextStyle(string type, string value);

public:
	StyleState* merge(StyleState* style);

public:
	int getInt(string key);
	double getDouble(string key);
	string getString(string key);
	Color getColor(string key);
;};
