#include "containers.h"
#include "../container.h"

Containers::Containers(vector<Container*>* objects)
{
	this->containers = objects;
}

Containers::~Containers()
{
	delete containers;
}

void Containers::addEventListener(string action, eventCallback event_callback)
{
	if (event_callback == nullptr || action.empty())
		return;

	for (auto& container : *containers)
	{
		container->addEventListener(action, event_callback);
	}

}

void Containers::each(eachCallback each_callback)
{
	if (each_callback == nullptr)
		return;

	for (auto& object : *containers)
	{
		each_callback(object);
	}
}
