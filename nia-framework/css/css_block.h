#pragma once

#include "css_block_state.h"

namespace CSS
{

class css_block
{
private:
	css_block_state _normal;
	css_block_state _hover;
	css_block_state _active;

	string _name;

public:
	css_block();
	css_block(string name);
	css_block(string name, bool general);

public:
	void mergeWith(css_block& block);

public:
	css_block_state& normal();
	css_block_state& hover();
	css_block_state& active();

	void normal(css_block_state new_block);
	void hover(css_block_state new_block);
	void active(css_block_state new_block);

	string name();
	void name(string name);
};


}