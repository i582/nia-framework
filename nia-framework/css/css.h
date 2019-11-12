#pragma once

#include "css_block.h"
#include "css_parse.h"

namespace CSS
{

using std::string;
using std::map;

class css
{
private:
	map<string, css_block> blocks;

	css_parser* parser;

public:
	css();
	css(string code);

	~css();
	
public:
	void open(string path);
	void parse();


	void add(css_block block);

public:
	css_block& operator[](const string key);
	css_block& at(const string key);

	void set_code(string code);
	void set_path(string path);

};

}