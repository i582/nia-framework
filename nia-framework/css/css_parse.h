#pragma once

#include "iostream"
#include "string"
#include "vector"
#include "map"


#include "css-attributes.h"

namespace CSS
{

using std::string;
using std::vector;
using std::map;

using std::cout;
using std::endl;

enum class TokenType
{
	ID_SIGN, // #
	CLASSNAME_SIGN, // .
	COLON, // :
	SEMICOLON, // ;
	LBRA, // {
	RBRA, // }

	FIELD
};

enum State
{
	NEXT_TOKEN_IS_ID,
	NEXT_TOKEN_IS_CLASSNAME,

	NEXT_TOKEN_IS_LBRA,

	NEXT_TOKEN_IS_COLON,
	NEXT_TOKEN_IS_SEMICOLON,

	NEXT_TOKEN_IS_ATTRIBUTE,
	NEXT_TOKEN_IS_VALUE,

	NEXT_TOKEN_IS_PSEUDO,

	END_BLOCK,

	START_PARSE
};

class css;

class css_block;

class css_parser
{
private:
	string filePath;

	FILE* file;
	string code;

	vector<string> tokens;

	vector< vector<string> > blocks;

	map <string, CSS::css_block> css_blocks;

	CSS::css* cssPlace;

	//vector<Styles*> styles;

	//map < string, Styles* > resultStyles;

public:
	css_parser(string filePath, CSS::css* cssPlace);
	css_parser(string code, bool isCode, CSS::css* cssPlace);

public:
	void parse();

private:
	void openFile();
	void deleteExcess();
	void deleteSpaceInCode();

private:
	bool isSplitSymbol(char symbol);
	TokenType whatIsToken(string token);

private:
	void splitByBlock();
	void splitByToken();

	void syntaxParseOneBlock(vector<string>& block);


	void syntaxParse();

	void mergeStyleComponent();

	void updateCSS();

public:
	//map < string, Styles* > getReadyStyles();

};

}