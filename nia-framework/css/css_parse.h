#pragma once

#include "iostream"
#include "string"
#include "vector"

#include "../utils/utils.h"
#include "../container/style/styles.h"

using std::string;
using std::vector;

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


class CssParse
{
private:
	string filePath;

	FILE* file;
	string code;

	vector<string> tokens;

	vector< vector<string> > blocks;

	vector<Styles*> styles;

	map < string, Styles* > resultStyles;

public:
	CssParse(string filePath);


private:
	void openFile();
	void deleteExcess();


private:
	bool isSplitSymbol(char symbol);
	TokenType whatIsToken(string token);

private:
	void splitByBlock();
	void splitByToken();

	void syntaxParseOneBlock(vector<string>& block);


	void syntaxParse();

	void mergeStyleComponent();

public:
	map < string, Styles* > getReadyStyles();

};