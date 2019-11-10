#include "styles.h"

Styles::Styles()
{
}

Styles::Styles(bool generalSetup)
{
	this->_normal = StyleState(true);
	this->_hover = StyleState(true);
	this->_active = StyleState(true);
}

Styles* Styles::mergeTo(Styles* style)
{
	this->_normal.mergeTo(&style->_normal);
	this->_hover.mergeTo(&style->_hover);
	this->_active.mergeTo(&style->_active);

	return this;
}

StyleState* Styles::normal()
{
	return &_normal;
}

StyleState* Styles::hover()
{
	return &_hover;
}

StyleState* Styles::active()
{
	return &_active;
}
