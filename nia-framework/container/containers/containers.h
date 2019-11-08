#pragma once

#include "../container-header.h"
using std::string;

class Containers
{
private:
	vector <Container*>* containers;

public:
	Containers(vector <Container*>* containers);
	~Containers();

public:
	void addEventListener(string action, eventCallback event_callback);
	void each(eachCallback each_callback);
};