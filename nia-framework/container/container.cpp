#include "container.h"
#include "../window/base/window.h"

Container::Container(string id, Rect size, string classNames)
{
	// main
	this->_id = id;
	this->_size = size;
	this->_classes = classNames;

	this->_outerSize = size;

	// parent
	this->_parent = nullptr;

	// childs
	this->_childs = {};
	this->_sizeChilds = {};

	// display
	this->_display = true;

	// event listeners
	this->eventListeners = {};
	this->setupEventListeners();

	// user data
	this->_userData = {};

	// state
	this->_isHovered = false;
	this->_isActive = false;

	// sdl
	this->_renderer = nullptr;
	this->_texture = nullptr;
	this->_outerTexture = nullptr;

	
	// styles part
	this->_style;
	this->_rawStyle;


	// Other for Events
	this->firstMouseMotion = false;
}



bool Container::isHovered()
{
	return _isHovered;
}

bool Container::isActive()
{
	return _isActive;
}

bool Container::hasClass(string className)
{
	return _classes.find(className) != -1;
}

Container* Container::removeClass(string className)
{
	int indexStart = _classes.find(className);

	if (indexStart == -1)
		return this;

	_classes.erase(_classes.begin() + indexStart, _classes.begin() + indexStart + className.length());

	return this;
}

Container* Container::addClass(string className)
{
	_classes += " " + className;
	return this;
}

Container* Container::toggleClass(string className)
{
	if (hasClass(className))
	{
		removeClass(className);
	}
	else
	{
		addClass(className);
	}

	return this;
}

void Container::render()
{
	if (!_display)
		return;

	color _background;
	color _border;

	
	if (_isHovered)
	{
		if (_isActive)
		{
			_background = _style.activeBackgroundColor();
			_border = _style.activeBorderColor();
		}
		else
		{
			_background = _style.hoverBackgroundColor();
			_border = _style.hoverBorderColor();
		}
	}
	else
	{
		_background = _style.backgroundColor();
		_border = _style.borderColor();
	}

	Uint8* background = (Uint8*)&_background;
	Uint8* border = (Uint8*)& _border;

	SDL_SetRenderTarget(_renderer, _texture);


	SDL_SetRenderDrawColor(_renderer, background[3], background[2], background[1], background[0]);
	SDL_RenderFillRect(_renderer, NULL);


	SDL_SetRenderDrawColor(_renderer, border[3], border[2], border[1], border[0]);
	SDL_RenderDrawRect(_renderer, NULL);


	for (auto& child : _childs)
	{
		child->render();
	}


	SDL_SetRenderTarget(_renderer, _outerTexture);

	size_t thickness = _style.shadow().thickness();
	size_t blur = _style.shadow().blur();

	Color cl = _style.shadow().startColor();
	Color cl1 = _style.shadow().endColor();

	Draw::roundedShadowRectangle(_renderer, thickness > blur ? thickness : blur, thickness > blur ? thickness : blur, _outerSize.w() - 2 * (thickness > blur ? thickness : blur), _outerSize.h() - 2 * (thickness > blur ? thickness : blur), 0, cl.color(), cl1.color(), thickness, blur);
	

	SDL_RenderCopy(_renderer, _texture, NULL, &_size.toSdlRect());



	SDL_Texture* parentTexture = nullptr;
	if (_parent != nullptr)
	{
		parentTexture = _parent->texture();
	}

	SDL_SetRenderTarget(_renderer, parentTexture);



	// TODO
	// src part textures
	Rect _sizeCopy = _size;

	Rect src = _sizeCopy;
	//src.x = 0; src.y = 0;

	SDL_RenderCopy(_renderer, _outerTexture, NULL, &_outerSize.toSdlRect());
}

void Container::setupEventListeners()
{
	eventListeners["click"] = Container::unusedCallback;
	eventListeners["hover"] = Container::unusedCallback;
	eventListeners["mousemotion"] = Container::unusedCallback;
	eventListeners["onmousedown"] = Container::unusedCallback;
	eventListeners["onmouseup"] = Container::unusedCallback;
	eventListeners["onmouseover"] = Container::unusedCallback;
	eventListeners["onmouseout"] = Container::unusedCallback;
}

Container* Container::getHoverElement(Point p)
{
	p.dx(-_size.x());
	p.dy(-_size.y());
	

	Container* hoverContainer = onChildHover(p);

	if (hoverContainer != nullptr)
	{
		return hoverContainer->getHoverElement(p);
	}
	else
	{
		return this;
	}
}

void Container::mouseButtonDown(Event* e)
{
	if (!_display)
		return;

	eventListeners["click"](this, e);
	eventListeners["onmousedown"](this, e);

	_isActive = true;
}

void Container::mouseButtonUp(Event* e)
{
	if (!_display)
		return;

	eventListeners["onmouseup"](this, e);

	_isActive = false;
}

void Container::mouseMotion(Event* e)
{
	if (!_display)
		return;

	if (firstMouseMotion == false)
	{
		eventListeners["onmouseover"](this, e);
		firstMouseMotion = true;
	}

	/*if (Object::hoverObject != this)
	{
		if (Object::hoverObject != nullptr && !Object::hoverObject->isChildrenObject(this))
		{
			Object::hoverObject->mouseOut(e);
		}

		Object::hoverObject = this;
	}*/


	_isHovered = true;
	//SDL_SetCursor(style->hoverCursor());

	eventListeners["mousemotion"](this, e);
	eventListeners["hover"](this, e);
}

void Container::mouseOut(Event* e)
{
}

ContainerStyle* Container::styles()
{
	return &_style;
}

void Container::computeSize()
{
	if (_parent != nullptr)
	{
		Rect parentSize = _parent->size();
		_size.calc(parentSize);
		_outerSize.calc(parentSize);
	}

	// adjust size with shadow size
	size_t shadowSize = _style.shadow().outerSize();

	_outerSize.size.dw(2 * shadowSize);
	_outerSize.size.dh(2 * shadowSize);

	_outerSize.start.dx(-(int)shadowSize);
	_outerSize.start.dy(-(int)shadowSize);

	_size.start.x(shadowSize);
	_size.start.y(shadowSize);



	this->_outerTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _outerSize.w(), _outerSize.h());
	SDL_SetTextureBlendMode(_outerTexture, SDL_BLENDMODE_BLEND);

	this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _size.w(), _size.h());
	SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);

	for (auto& child : _childs)
	{
		child->computeSize();
	}
}

void Container::computeChildrenSize()
{
	int width = 0;
	int height = 0;

	int maxWidth = 0;
	int maxHeight = 0;

	for (auto& child : _childs)
	{
		if (!child->display())
			continue;

		width = child->width() + child->left();
		height = child->height() + child->top();

		if (width > maxWidth)
			maxWidth = width;

		if (height > maxHeight)
			maxHeight = height;
	}


	_sizeChilds = { 0, 0, maxWidth, maxHeight };


	Size newTextureSize = _size.size;

	if (maxWidth > _size.w())
	{
		newTextureSize.w(maxWidth);
	}

	if (maxHeight > _size.h())
	{
		newTextureSize.w(maxHeight);
	}
	

	if (newTextureSize != _size.size || this->_texture == nullptr)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, newTextureSize.w(), newTextureSize.h());
	}
	


	for (auto& child : _childs)
	{
		child->computeChildrenSize();
	}
}

void Container::setupChildrenRenderer()
{
	if (this->_renderer == nullptr && this->_parent != nullptr)
	{
		this->_renderer = _parent->renderer();
	}

	for (auto& child : _childs)
	{
		child->setupChildrenRenderer();
	}
}

void Container::setupContainer()
{
	setupChildrenRenderer();
	computeSize();
	computeChildrenSize();
}

Container* const Container::parent()
{
	return _parent;
}

vector<Container*>& Container::childs()
{
	return _childs;
}

Container* Container::append(Container* obj)
{
	if (obj != nullptr)
	{
		this->_childs.push_back(obj);
		obj->_parent = this;

		Window::addObject(obj);
	}

	return obj;
}

Container* Container::appends(vector<Container*> containers)
{
	for (auto& object : containers)
	{
		append(object);
	}

	return this;
}

bool Container::isChildrenObject(Container* obj)
{
	bool is_child = false;

	if (_childs.size() == 0)
	{
		is_child = this == obj;
	}
	else
	{
		for (auto& child : _childs)
		{
			is_child |= child->isChildrenObject(obj);
		}
	}

	return is_child;
}

bool Container::isParentObject(Container* obj)
{
	bool is_parent = false;

	if (_parent == nullptr)
	{
		is_parent = this == obj;
	}
	else
	{
		is_parent |= _parent->isParentObject(obj);
	}

	return is_parent;
}

bool Container::onHover(Point point)
{
	return point.in(_size) && _display;
}

// TODO
Container* const Container::onChildHover(Point point)
{
	return nullptr;
}

int Container::width()
{
	return _size.w();
}

int Container::height()
{
	return _size.h();
}

int Container::top()
{
	return _size.y();
}

int Container::left()
{
	return _size.x();
}

Rect Container::size()
{
	return _size;
}

Rect Container::outerSize()
{
	return _outerSize;
}

void Container::addEventListener(string action, eventCallback callback_function)
{
	eventListeners[action] = callback_function;
}

void Container::removeEventListener(string action)
{
	eventListeners[action] = Container::unusedCallback;
}

void Container::callEventListener(string action, Event* e)
{
	if (eventListeners.find(action) != eventListeners.end())
	{
		eventListeners[action](this, e);
	}
}

map<string, void*>& Container::userData()
{
	return _userData;
}

void Container::userData(string key, void* data)
{
	_userData.insert(make_pair(key, data));
}

SDL_Renderer* const Container::renderer()
{
	return _renderer;
}

SDL_Texture* const Container::texture()
{
	return _texture;
}

Container* Container::show()
{
	_display = true;
	return this;
}

Container* Container::hide()
{
	_display = false;
	return this;
}

Container* Container::toggleDisplay()
{
	_display = !_display;
	return this;
}

bool Container::display()
{
	return _display;
}
