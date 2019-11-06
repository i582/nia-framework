#include "object.h"

Object* Object::hoverObject = nullptr;

Object::Object(string id, Rect sizeRaw, SDL_Renderer* renderer, Object* parent)
{
	this->_id = id;

	this->_parent = parent;
	this->_renderer = renderer;
	this->_texture = nullptr;
	this->_childrens = {};
	this->_sizeChildrens = {};

	this->firstMouseMotion = false;
	this->setupEventListeners();

	this->style = new ObjectStyle;

	this->is_hovered = false;
	this->is_active = false;

	this->classes = {};

	this->_display = true;

	// scroll part
	this->scrollY_Pos = 0;
	this->scrollY_Val = 0;
	this->scrollY_Delta = 0;

	this->scrollY_Visible = false;

	this->scrollY_Width = 18;
	this->scrollY_Height = -1;

	this->scrollY_Active = false;

	this->scrollY_SliderWidth = 13;
	this->scrollY_SliderHeight = -1;
}

Object::Object(string id, Rect sizeRaw, SDL_Renderer* renderer, string classNames) : Object(id, sizeRaw, renderer, nullptr)
{
	this->classes = classNames;
}

Object::Object(string id, Rect sizeRaw, string classNames) : Object(id, sizeRaw, nullptr, classNames)
{
}

void Object::setupEventListeners()
{

	eventListeners["click"] = Object::unusedCallback;
	eventListeners["hover"] = Object::unusedCallback;
	eventListeners["mousemotion"] = Object::unusedCallback;
	eventListeners["onmousedown"] = Object::unusedCallback;
	eventListeners["onmouseup"] = Object::unusedCallback;
	eventListeners["onmouseover"] = Object::unusedCallback;
	eventListeners["onmouseout"] = Object::unusedCallback;
}

void Object::addEventListener(string action, callback callback_function)
{
	eventListeners[action] = callback_function;
}

void Object::resetFirstMouseMotion()
{
	firstMouseMotion = false;
}

SDL_Texture* Object::texture()
{
	return _texture;
}

void Object::computeSize()
{
	if (_parent != nullptr)
	{
		Rect parentSize = _parent->size();
		_size.calc(parentSize);
	}

	this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _size.w(), _size.h());
	SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);


	this->scrollY_Height = _size.h();

	for (auto& child : _childrens)
	{
		child->computeSize();
	}
}

void Object::computeChildrenSize()
{
	int width = 0;
	int height = 0;

	int maxWidth = 0;
	int maxHeight = 0;

	for (auto& child : _childrens)
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


	_sizeChildrens = { 0, 0, maxWidth, maxHeight };

	bool needNewWidth = false;
	bool needNewHeight = false;

	if (maxWidth > _size.w())
	{
		cout << _id << " ����� ����� �� ������� �� x" << endl;
		needNewWidth = true;
	}
	
	if (maxHeight > _size.h())
	{
		cout << _id << " ����� ����� �� ������� �� y" << endl;
		needNewHeight = true;

		scrollY_Delta = maxHeight - _size.h();
		scrollY_Val = 0;
		scrollY_Visible = true;
	}
	else
	{
		scrollY_Delta = 0;
		scrollY_Val = 0;
		scrollY_Visible = false;
	}

	if (needNewWidth)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _sizeChildrens.w(), _size.h());
	}
	else if (needNewHeight)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _size.w(), _sizeChildrens.h());
	}
	else if (needNewWidth && needNewHeight)
	{
		SDL_DestroyTexture(this->_texture);
		this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _sizeChildrens.w(), _sizeChildrens.h());
	}

	for (auto& child : _childrens)
	{
		child->computeChildrenSize();
	}
}

void Object::setupChildrenRenderer()
{
	if (this->_renderer == nullptr && this->_parent != nullptr)
	{
		this->_renderer = _parent->renderer();
	}

	for (auto& child : _childrens)
	{
		child->setupChildrenRenderer();
	}
}

void Object::setupContainer()
{
	setupChildrenRenderer();
	computeSize();
	computeChildrenSize();
}

void Object::renderScrollY()
{
	if (!scrollY_Visible)
		return;

	Rect bodyRenderRect = { _size.w() - scrollY_Width, scrollY_Val , scrollY_Width, scrollY_Height };

	SDL_SetRenderDrawColor(_renderer, 0x3E, 0x3E, 0x42, 0xff);
	SDL_RenderFillRect(_renderer, &bodyRenderRect.toSDLRect());

	if (_sizeChildrens.h() != 0)
		scrollY_SliderHeight = (double)_size.h() / _sizeChildrens.h() * scrollY_Height;
	else
		scrollY_SliderHeight = 0;

	Rect sliderRenderRect = { bodyRenderRect.start._x + 3, scrollY_Val + (int)(scrollY_Pos * (scrollY_Height - scrollY_SliderHeight)), scrollY_SliderWidth, scrollY_SliderHeight };

	SDL_SetRenderDrawColor(_renderer, 0xff, 0x00, 0x68, 0xff);
	SDL_RenderFillRect(_renderer, &sliderRenderRect.toSDLRect());
}

Object* const Object::parent()
{
	return _parent;
}

vector<Object*>* const Object::childrens()
{
	return &_childrens;
}

int Object::width()
{
	return _size.w();
}

int Object::height()
{
	return _size.h();
}

int Object::top()
{
	return _size.y();
}

int Object::left()
{
	return _size.x();
}

Rect Object::size()
{
	return _size;
}

ObjectStyle* Object::styles()
{
	return style;
}

ObjectStyle* Object::styles(ObjectStyle* newStyle)
{
	this->style = newStyle;
	return style;
}

Object* Object::show()
{
	_display = true;

	//Window::getElementById("main-container")->computeChildrenSize();

	return this;
}

Object* Object::hide()
{
	_display = false;

	//Window::getElementById("main-container")->computeChildrenSize();

	return this;
}

Object* Object::toggleDisplay()
{
	_display = !_display;

	//Window::getElementById("main-container")->computeChildrenSize();

	return this;
}

bool Object::display()
{
	return _display;
}

Object* Object::append(Object* obj)
{
	if (obj != nullptr)
	{
		this->_childrens.push_back(obj);

		obj->_parent = this;

		//Window::addObject(obj);
	}

	return obj;
}

Object* Object::appendSomeObjects(vector<Object*> someObjects)
{
	for (auto& object : someObjects)
	{
		append(object);
	}

	return this;
}

bool Object::onHover(Point point)
{
	if (scrollY_Delta != 0)
	{
		Rect tempSize = _size;
		tempSize.start._y -= scrollY_Val;

		return point.in(tempSize);
	}

	return point.in(_size);
}

Object* const Object::onChildHover(Point point)
{
	for (auto& child : _childrens)
	{
		if (child->onHover(point) && child->display())
		{
			return child;
		}
	}

	return nullptr;
}

/*
 * @brief ���������, �������� �� ������ �������� �������
 *
 */
bool Object::isChildrenObject(Object* obj)
{
	bool is_child = false;

	if (_childrens.size() == 0)
	{
		is_child = this == obj;
	}
	else
	{
		for (auto& child : _childrens)
		{
			is_child |= child->isChildrenObject(obj);
		}
	}

	return is_child;
}

/*
 * @brief ���������, �������� �� ������ ������������ �������
 *
 */
bool Object::isParentObject(Object* obj)
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


Object* Object::getHoverElement(SDL_Event* e)
{
	e->motion.x -= _size.x();
	e->motion.y -= _size.y();

	Object* hoverObject = onChildHover({ e->motion.x, e->motion.y });

	if (hoverObject != nullptr)
	{
		return hoverObject->getHoverElement(e);
	}
	else
	{
		return this;
	}
}

Object* Object::getFirstScrollableParent()
{
	if (this->_parent != nullptr)
	{
		if (this->_parent->scrollY_Delta != 0 && this->_parent->display())
		{
			return this->_parent;
		}
		else
		{
			return this->_parent->getFirstScrollableParent();
		}
	}
	
	
	return nullptr;
}

void Object::mouseButtonDown(SDL_Event* e)
{
	if (!_display)
		return;

	eventListeners["click"](this, e);
	eventListeners["onmousedown"](this, e);

	is_active = true;

	//Window::getElementById("main-container")->update();
}

void Object::mouseButtonUp(SDL_Event* e)
{
	if (!_display)
		return;

	eventListeners["onmouseup"](this, e);

	is_active = false;

	//Window::getElementById("main-container")->update();
}

void Object::mouseMotion(SDL_Event* e)
{
	if (!_display)
		return;

	if (firstMouseMotion == false)
	{
		eventListeners["onmouseover"](this, e);
		firstMouseMotion = true;
	}

	if (Object::hoverObject != this)
	{	
		if (Object::hoverObject != nullptr && !Object::hoverObject->isChildrenObject(this))
		{
			Object::hoverObject->mouseOut(e);
		}
		
		Object::hoverObject = this;
	}

	
	is_hovered = true;
	SDL_SetCursor(style->hoverCursor());

	eventListeners["mousemotion"](this, e);
	eventListeners["hover"](this, e);

	//Window::getElementById("main-container")->update();
}

void Object::mouseOut(SDL_Event* e)
{
	if (!_display)
		return;

	eventListeners["onmouseout"](this, e);
	is_hovered = false;
	SDL_SetCursor(style->cursor());
}

void Object::mouseScroll(SDL_Event* e, int direction)
{
	if (!_display)
		return;

	if (scrollY_Delta != 0)
	{
		
		if (direction < 0)
			scrollY_Val += 20;
		else 
			scrollY_Val -= 20;
		
	
		if (scrollY_Val > scrollY_Delta)
			scrollY_Val = scrollY_Delta;
		if (scrollY_Val < 0)
			scrollY_Val = 0;

		scrollY_Pos = scrollY_Val / (double)scrollY_Delta;

		cout << scrollY_Pos << endl;
	}
	else
	{
		Object* firstScrollableParent = getFirstScrollableParent();

		if (firstScrollableParent != nullptr)
		{
			firstScrollableParent->mouseScroll(e, direction);
		}
	}

	//Window::getElementById("main-container")->update();
}

SDL_Renderer* Object::renderer()
{
	return _renderer;
}

bool Object::hasClass(string className)
{
	return classes.find(className) != -1;
}

Object* Object::removeClass(string className)
{
	int indexStart = classes.find(className);

	if (indexStart == -1)
		return this;

	classes.erase(classes.begin() + indexStart, classes.begin() + indexStart + className.length());

	return this;
}

Object* Object::addClass(string className)
{
	classes += " " + className;
	return this;
}

Object* Object::toggleClass(string className)
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








ObjectStyle::ObjectStyle()
{
	this->_backgroundColor = this->_hoverBackgroundColor = this->_activeBackgroundColor = 0xffffffff;
	this->_textColor = 0x000000ff;

	this->_borderColor = this->_hoverBorderColor = this->_activeBorderColor = 0xffffff00;

	this->_cursor = this->_hoverCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
}

ObjectStyle::~ObjectStyle()
{
	SDL_FreeCursor(_cursor);
	SDL_FreeCursor(_hoverCursor);
}

color ObjectStyle::backgroundColor()
{
	return _backgroundColor;
}

color ObjectStyle::textColor()
{
	return _textColor;
}

color ObjectStyle::hoverBackgroundColor()
{
	return _hoverBackgroundColor;
}

SDL_Cursor* ObjectStyle::cursor()
{
	return _cursor;
}

ObjectStyle* ObjectStyle::cursor(string cursor_id)
{
	if (cursor_id == "arrow")
	{
		_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	}
	else if (cursor_id == "hand")
	{
		_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}

	return this;
}

SDL_Cursor* ObjectStyle::hoverCursor()
{
	return _hoverCursor;
}

ObjectStyle* ObjectStyle::hoverCursor(string cursor_id)
{

	if (cursor_id == "arrow")
	{
		_hoverCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	}
	else if (cursor_id == "hand")
	{
		_hoverCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}

	return this;
}

ObjectStyle* ObjectStyle::backgroundColor(color newColor)
{
	_backgroundColor = _hoverBackgroundColor = _activeBackgroundColor = newColor;
	return this;
}

ObjectStyle* ObjectStyle::textColor(color newColor)
{
	_textColor = newColor;
	return this;
}

ObjectStyle* ObjectStyle::hoverBackgroundColor(color newColor)
{
	_hoverBackgroundColor = newColor;
	return this;
}

color ObjectStyle::activeBackgroundColor()
{
	return _activeBackgroundColor;
}

ObjectStyle* ObjectStyle::activeBackgroundColor(color newColor)
{
	_activeBackgroundColor = newColor;
	return this;
}

color ObjectStyle::borderColor()
{
	return _borderColor;
}

color ObjectStyle::hoverBorderColor()
{
	return _hoverBorderColor;
}

color ObjectStyle::activeBorderColor()
{
	return _activeBorderColor;
}

ObjectStyle* ObjectStyle::borderColor(color newColor)
{
	_borderColor = _hoverBorderColor = _activeBorderColor = newColor;
	return this;
}

ObjectStyle* ObjectStyle::hoverBorderColor(color newColor)
{
	_hoverBorderColor = newColor;
	return this;
}

ObjectStyle* ObjectStyle::activeBorderColor(color newColor)
{
	_activeBorderColor = newColor;
	return this;
}
