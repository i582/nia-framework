#include "objects.h"
#include "object.h"

Objects::Objects(vector<Object*>* objects)
{
	this->objects = objects;
}

Objects::~Objects()
{
	delete objects;
}

void Objects::addEventListener(string action, callback callback_function)
{
	if (callback_function == nullptr || action.empty())
		return;

	for (auto& object : *objects)
	{
		object->addEventListener(action, callback_function);
	}

}

void Objects::each(callbackEach callback_function)
{
	if (callback_function == nullptr)
		return;

	for (auto& object : *objects)
	{
		callback_function(object);
	}
}
