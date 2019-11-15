#include "container.h"
#include "../window/base/window.h"

Container* Container::hoverContainer = nullptr;

Container::Container(string id, Rect size, string classNames)
{
	// main
	this->_id = id;
	this->_innerSize = size;
	this->_classes = classNames;

	this->_outerSize = size;

	// parent
	this->_parent = nullptr;
	this->_window = nullptr;

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


	// styles
	this->_cssBlock = CSS::css_block(id, true);


	// Other for Events
	this->firstMouseMotion = false;

	// scroll
	this->scroll = new Scroll(_renderer, { 0, 0, 20, 0 }, 0, 1);
	this->scrollable = false;

	// text
	Font::root("../nia-framework/fonts/");
	this->_font = new Font("consolas");
	this->_text = new Text(this, "", { 0,0,0,0 }, _font, 14, Color("#000000"));



	// image
	this->_image = nullptr;
}

Container::~Container()
{
	SDL_DestroyTexture(_texture);
	SDL_DestroyTexture(_outerTexture);

	delete scroll;
	delete _text;
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


	_window->handleStyles();
	return this;
}

Container* Container::addClass(string className)
{
	_classes += " " + className;

	_window->handleStyles();
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

Text* Container::text()
{
	return _text;
}

void Container::render()
{
	if (!_display)
		return;

	SDL_SetRenderTarget(_renderer, _outerTexture);
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0x00);
	SDL_RenderClear(_renderer);

	SDL_SetRenderTarget(_renderer, _texture);
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0x00);
	SDL_RenderClear(_renderer);


	CSS::css_block_state* blockState = &_cssBlock.normal();

	
	if (_isHovered)
	{
		if (_isActive)
		{
			blockState = &_cssBlock.active();
		}
		else
		{
			blockState = &_cssBlock.hover();
		}
	}


	SDL_SetRenderTarget(_renderer, _texture);


	Color _bk = blockState->get<Color>("background-color");
	Color _br = blockState->get<Color>("border-color");

	int borderRadius = blockState->get<int>("border-radius");

	roundedBoxColor(_renderer, 0, 0, _innerSize.w(), _innerSize.h(), borderRadius, _bk.color());



	if (this->_image != nullptr)
	{
		string path = blockState->get<string>("background-image");
		this->_image->setPath(path);

		int x_shift = blockState->get<int>("background-position-x");
		int y_shift = blockState->get<int>("background-position-y");

		this->_image->setImageShift({ x_shift, y_shift });

		this->_image->render();
	}
		






	_text->setColor(&blockState->get<Color>("color"));
	_text->setFontSize(blockState->get<int>("font-size"));
	_text->setLineHeight(blockState->get<double>("line-height"));
	_text->setTextAlign(blockState->get<string>("text-align"));
	_text->setTextBlockVerticalAlign(blockState->get<string>("vertical-align"));

	_text->setTextBlockMargin("top", blockState->get<int>("margin-top"));
	_text->setTextBlockMargin("bottom", blockState->get<int>("margin-bottom"));
	_text->setTextBlockMargin("left", blockState->get<int>("margin-left"));
	_text->setTextBlockMargin("right", blockState->get<int>("margin-right"));

	_text->render();

	for (auto& child : _childs)
	{
		child->render();
	}


	SDL_SetRenderTarget(_renderer, _outerTexture);

	/*size_t thickness = _style.shadow().thickness();
	size_t blur = _style.shadow().blur();

	Color cl = _style.shadow().startColor();
	Color cl1 = _style.shadow().endColor();

	Draw::roundedShadowRectangle(_renderer, thickness > blur ? thickness : blur, thickness > blur ? thickness : blur, _outerSize.w() - 2 * (thickness > blur ? thickness : blur), _outerSize.h() - 2 * (thickness > blur ? thickness : blur), 0, cl.color(), cl1.color(), thickness, blur);
	
	SDL_SetRenderDrawColor(_renderer, 0xff, 0x00, 0xff, 0xff);
	SDL_RenderDrawRect(_renderer, NULL);*/

	
	int topSize = blockState->get<int>("border-top-size");
	int bottomSize = blockState->get<int>("border-bottom-size");
	int leftSize = blockState->get<int>("border-left-size");
	int rightSize = blockState->get<int>("border-right-size");
	
	 
	roundedBoxColor(_renderer, _innerSize.x() - leftSize, _innerSize.y() - topSize,
		_innerSize.x() + _innerSize.w() - 1 + rightSize, _innerSize.y() + _innerSize.h() - 1 + bottomSize, borderRadius, _br.color());







	Rect copy = _innerSize;
	copy.x(0); copy.y(this->scroll->_nowValue);

	SDL_RenderCopy(_renderer, _texture, &copy.toSdlRect(), &_innerSize.toSdlRect());


	this->scroll->render();


	SDL_Texture* parentTexture = nullptr;
	if (_parent != nullptr)
	{
		parentTexture = _parent->texture();
	}

	SDL_SetRenderTarget(_renderer, parentTexture);



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
	p.dx(-_innerSize.x());
	p.dy(-_innerSize.y());
	
	

	Container* hoverContainer = onContainerHover(p);

	if (hoverContainer != nullptr)
	{
		return hoverContainer->getHoverElement(p);
	}
	else
	{
		return this;
	}
}

Container* Container::getFirstScrollableParent()
{
	if (this->_parent != nullptr)
	{
		if (this->_parent->isScrollable())
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

void Container::mouseButtonDown(Event* e)
{
	if (!_display)
		return;

	if (scroll->onHover({ e->motion.x, e->motion.y }))
	{
		cout << "gssgsg" << endl;
	}

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

	if (hoverContainer != this)
	{
		bool aaa = false;

		if (hoverContainer != nullptr && !hoverContainer->isChildrenObject(this))
		{
			hoverContainer->mouseOut(e);
		}
		
		hoverContainer = this;
	}


	_isHovered = true;
	//SDL_SetCursor(style->hoverCursor());

	eventListeners["mousemotion"](this, e);
	eventListeners["hover"](this, e);
}

void Container::mouseOut(Event* e)
{
	if (!_display)
		return;

	eventListeners["onmouseout"](this, e);
	_isHovered = false;
	firstMouseMotion = false;
	//SDL_SetCursor(style->cursor());
}

void Container::mouseScroll(Event* e, int scrollDirection)
{
	if (!_display)
		return;

	if (!scrollable)
	{
		Container* firstScrollableParent = getFirstScrollableParent();

		if (firstScrollableParent != nullptr)
		{
			firstScrollableParent->mouseScroll(e, scrollDirection);
		}

		return;
	}

	if (scrollDirection < 0)
		scroll->shift(20);
	else
		scroll->shift(-20);
}

CSS::css_block& Container::styles()
{
	return _cssBlock;
}

void Container::computeSize()
{
	if (_parent != nullptr)
	{
		Rect parentSize = _parent->size();
		_innerSize.calc(parentSize);
		_outerSize.calc(parentSize);
	}



	int topSize = std::_Max_value(std::_Max_value(_cssBlock.normal().get<int>("border-top-size"),
		_cssBlock.hover().get<int>("border-top-size")), _cssBlock.active().get<int>("border-top-size"));
	int bottomSize = std::_Max_value(std::_Max_value(_cssBlock.normal().get<int>("border-bottom-size"),
		_cssBlock.hover().get<int>("border-bottom-size")), _cssBlock.active().get<int>("border-bottom-size"));
	int leftSize = std::_Max_value(std::_Max_value(_cssBlock.normal().get<int>("border-left-size"),
		_cssBlock.hover().get<int>("border-left-size")), _cssBlock.active().get<int>("border-left-size"));
	int rightSize = std::_Max_value(std::_Max_value(_cssBlock.normal().get<int>("border-right-size"),
		_cssBlock.hover().get<int>("border-right-size")), _cssBlock.active().get<int>("border-right-size"));



	_outerSize.size.dw(leftSize + rightSize);
	_outerSize.size.dh(topSize + bottomSize);

	_outerSize.start.dx(-leftSize);
	_outerSize.start.dy(-topSize);

	_innerSize.start.x(leftSize);
	_innerSize.start.y(topSize);


	this->_text->setSize({ 0,0,_innerSize.w(), _innerSize.h() });



	this->_outerTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _outerSize.w(), _outerSize.h());
	SDL_SetTextureBlendMode(_outerTexture, SDL_BLENDMODE_BLEND);

	this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _innerSize.w(), _innerSize.h());
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


	Size newTextureSize = _innerSize.size;

	if (maxWidth > _innerSize.w())
	{
		newTextureSize.w(maxWidth);
	}

	if (maxHeight > _innerSize.h())
	{
		newTextureSize.h(maxHeight);



		/*
		 * Setup scroll
		 */
		this->scroll->_bodySize.x(_innerSize.x() + _innerSize.w());
		this->scroll->_bodySize.y(_innerSize.y());

		this->scroll->_bodySize.h(_innerSize.h());

		this->scroll->_maxValue = newTextureSize.h() - _innerSize.h();

		this->scroll->_relSizes = _innerSize.h() / (double)newTextureSize.h();
		this->scroll->_renderer = _renderer;
		this->scroll->init();

		_outerSize.dw(this->scroll->_bodySize.w());

		SDL_DestroyTexture(this->_outerTexture);
		this->_outerTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _outerSize.w(), _outerSize.h());
		SDL_SetTextureBlendMode(_outerTexture, SDL_BLENDMODE_BLEND);

		this->scroll->_parentTexture = this->_outerTexture;
		this->scrollable = true;
	}
	

	if (newTextureSize != _innerSize.size || this->_texture == nullptr)
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

		// set-up text
		this->_text->setRenderer(this->_renderer);
	}

	for (auto& child : _childs)
	{
		child->setupChildrenRenderer();
	}
}

void Container::setupBackgroundImage()
{
	this->_image = new Image(this);

	for (auto& child : _childs)
	{
		child->setupBackgroundImage();
	}
}

void Container::setupContainer()
{
	setupChildrenRenderer();

	computeSize();
	computeChildrenSize();

	setupBackgroundImage();
}

Container* const Container::parent()
{
	return _parent;
}

vector<Container*>& Container::childs()
{
	return _childs;
}

Window* Container::window()
{
	return _window;
}

Container* Container::append(Container* obj)
{
	if (obj != nullptr)
	{
		this->_childs.push_back(obj);
		obj->_parent = this;
		obj->_window = this->_window;

		_window->addObject(obj);
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

	is_child = this == obj;
	

	if (_childs.size() != 0 && is_child == false)
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
	return point.in(_outerSize) && _display;
}

Container* const Container::onContainerHover(Point point)
{
	point.dy(scroll->_nowValue);

	for (int i = _childs.size() - 1; i >= 0; i--)
	{
		auto& child = _childs[i];

		if (child->onHover(point))
		{
			// adjust coord
			point = point - child->outerSize().start;

			return child->onContainerHover(point);
		}
	}

	return this;
}

int Container::width()
{
	return _innerSize.w();
}

int Container::height()
{
	return _innerSize.h();
}

int Container::top()
{
	return _outerSize.y();
}

int Container::left()
{
	return _outerSize.x();
}

Rect Container::size()
{
	return _innerSize;
}

Rect Container::outerSize()
{
	return _outerSize;
}

string Container::id()
{
	return _id;
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

void Container::addUserData(string key, void* data)
{
	_userData.insert(make_pair(key, data));
}

void* Container::userData(string key)
{
	return _userData[key];
}

SDL_Renderer* const Container::renderer()
{
	return _renderer;
}

SDL_Texture* const Container::texture()
{
	return _texture;
}

bool Container::isScrollable()
{
	return scrollable;
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
