#include "window.h"

ContainerStyleRaw* Window::addStyle(string className, ContainerStyleRaw* style)
{
	__containersStyles.insert(make_pair(className, style));
	return style;
}

void Window::handleStyles()
{

	for (auto& style : __containersStyles)
	{
		string className = style.first;

		for (auto& container : __containers)
		{
			if (container.second->hasClass(className))
			{
				style.second->updateStyle(container.second->styles());
			}
		}

	}

}

Container* Window::addObject(Container* obj)
{
	if (obj == nullptr)
		return nullptr;

	string objectId = obj->_id;

	if (__containers.find(objectId) != __containers.end())
	{
		cout << "Ёлемент с id = " << objectId << " уже существует!" << endl;
		return nullptr;
	}
	else
	{
		__containers.insert(make_pair(objectId, obj));
	}

	return obj;
}

Container* Window::getElementById(string id)
{
	Container* obj = __containers[id];
	if (obj == nullptr)
	{
		cout << "Ёлемент с id = " << id << " не существует!" << endl;
		return nullptr;
	}
	else
	{
		return obj;
	}
}


Containers* Window::getElementsByClassName(string className)
{
	vector<Container*>* containerVector = new vector<Container*>;
	for (auto& container : __containers)
	{
		if (container.second->hasClass(className))
		{
			containerVector->push_back(container.second);
		}
	}

	return new Containers(containerVector);
}



Window::Window(string title, Rect size)
{
	this->title = title;
	this->size = size;

	this->window = nullptr;
	this->renderer = nullptr;

	this->display = true;

	

	this->init();
	this->generalSetup();
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

bool Window::init()
{
	this->window = SDL_CreateWindow(title.c_str(), 
		size.x() == -1 ? SDL_WINDOWPOS_CENTERED : size.x(),
		size.y() == -1 ? SDL_WINDOWPOS_CENTERED : size.y(),
		size.w(), size.h(), NULL);

	if (window == nullptr)
	{
		cout << "Error of initialize new Window: " << SDL_GetError() << endl;
		return false;
	}

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
		return false;
	}

	return true;
}

void Window::generalSetup()
{
	__container = new MainContainer(this);
	Window::addObject(__container);
}

void Window::show()
{
	display = true;

	SDL_ShowWindow(window);
}

void Window::hide()
{
	display = false;

	SDL_HideWindow(window);
}

bool Window::isShow()
{
	return display;
}

void Window::close()
{
	SDL_DestroyWindow(window);
}

Rect Window::getSize()
{
	return size;
}

SDL_Renderer* Window::getRenderer()
{
	return renderer;
}

SDL_Window* Window::getWindow()
{
	return window;
}

//Object* Window::addObject(Object* obj)
//{
//	if (obj == nullptr)
//		return nullptr;
//
//	string objectId = obj->_id;
//
//	if (containers.find(objectId) != containers.end())
//	{
//		cout << "Ёлемент с id = " << objectId << " уже существует!" << endl;
//		return nullptr;
//	}
//	else
//	{
//		containers.insert(make_pair(objectId, obj));
//	}
//
//	update();
//
//	return obj;
//}
