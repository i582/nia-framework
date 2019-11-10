#pragma once

#include "style-state.h"

class CssParse;

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
	friend CssParse;

public:
	Styles* mergeTo(Styles* style);

public:
	StyleState* normal();
	StyleState* hover();
	StyleState* active();

};