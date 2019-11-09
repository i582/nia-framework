#pragma once

#include "style-state.h"

class Styles
{
private:
	StyleState _normal;
	StyleState _hover;
	StyleState _active;

public:
	Styles();
	Styles(bool generalSetup);

public:
	friend Styles;

public:
	Styles* merge(Styles* style);

public:
	StyleState* normal();
	StyleState* hover();
	StyleState* active();

};