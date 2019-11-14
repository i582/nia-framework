#include "css.h"

CSS::css::css()
{
	this->parser = nullptr;
}

CSS::css::css(string path)
{
	this->parser = new css_parser(path, this);
	parse();
}

CSS::css::css(string code, bool isCode)
{
	this->parser = new css_parser(code, true, this);
	parse();
}

CSS::css::~css()
{
	delete parser;
}

void CSS::css::open(string path)
{
	delete parser;
	this->parser = new css_parser(path, this);
	parse();
}

void CSS::css::parse()
{
	if (this->parser != nullptr)
	{
		parser->parse();
	}
	else
	{
		cout << "ERROR: parser not configured. Set the code or path to the CSS file!" << endl;
	}
}

void CSS::css::add(css_block block)
{
	blocks[block.name()] = block;
}

CSS::css_block& CSS::css::operator[](const string key)
{
	return at(key);
}

CSS::css_block& CSS::css::at(const string key)
{
	if (blocks.find(key) == blocks.end())
	{
		cout << "ERROR: Block with id/classname" << key << " NOT found!" << endl;
	}

	return blocks[key];
}

void CSS::css::set_code(string code)
{
	delete parser;
	this->parser = new css_parser(code, true, this);
}

CSS::map<string, CSS::css_block>& CSS::css::getStyles()
{
	return blocks;
}
