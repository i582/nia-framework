#include "css_parse.h"
#include "css.h"


CSS::css_parser::css_parser(string filePath, CSS::css* cssPlace)
{
	if (cssPlace == nullptr)
	{
		cout << "ERROR: cssPlace is nullptr" << endl;
		return;
	}

	this->cssPlace = cssPlace;
	this->filePath = filePath;

	openFile();
}

CSS::css_parser::css_parser(string code, bool isCode, CSS::css* cssPlace)
{
	if (cssPlace == nullptr)
	{
		cout << "ERROR: cssPlace is nullptr" << endl;
		return;
	}

	this->cssPlace = cssPlace;
	this->code = code;

	deleteSpaceInCode();
}

void CSS::css_parser::parse()
{
	splitByToken();
	splitByBlock();
	syntaxParse();
	mergeStyleComponent();
	updateCSS();
}

void CSS::css_parser::openFile()
{
	file = fopen(filePath.c_str(), "r");

	while (1)
	{
		if (getc(file) == EOF) break;
		else fseek(file, -1, SEEK_CUR);

		deleteExcess();
		code += getc(file);

	}

	fclose(file);

	std::cout << code << std::endl;
}

void CSS::css_parser::deleteExcess()
{
	char symbol = -1;

	while (1)
	{
		symbol = getc(file);

		if (symbol == ' ')
		{

			symbol = getc(file);
			while (symbol == ' ' && symbol != EOF)
			{
				symbol = getc(file);
			}

			//fseek(file, -1, SEEK_CUR);

		}


		if (!(symbol == '\t' || symbol == '\n' || symbol == '\r'))
		{
			fseek(file, -1, SEEK_CUR);
			break;
		}

		

		if (symbol == EOF)
			break;
	}
}

void CSS::css_parser::deleteSpaceInCode()
{
	string newCode;

	for (auto& symbol : code)
	{
		if (symbol != ' ')
		{
			newCode += symbol;
		}
	}

	code = newCode;
}

bool CSS::css_parser::isSplitSymbol(char symbol)
{
	return symbol == ':' || symbol == '.' || symbol == '#' || symbol == ';' || symbol == '{' || symbol == '}';
}

CSS::TokenType CSS::css_parser::whatIsToken(string token)
{
	if (token == ".")
	{
		return TokenType::CLASSNAME_SIGN;
	}
	else if (token == "#")
	{
		return TokenType::ID_SIGN;
	}
	else if (token == ":")
	{
		return TokenType::COLON;
	}
	else if (token == ";")
	{
		return TokenType::SEMICOLON;
	}
	else if (token == "{")
	{
		return TokenType::LBRA;
	}
	else if (token == "}")
	{
		return TokenType::RBRA;
	}
	else
	{
		return TokenType::FIELD;
	}
}

void CSS::css_parser::splitByBlock()
{
	vector<string> tempBlock;

	for (auto& token : tokens)
	{
		if (token != "}")
		{
			tempBlock.push_back(token);
		}
		else
		{
			tempBlock.push_back(token);
			blocks.push_back(tempBlock);
			tempBlock.clear();
		}
		
	}

}

void CSS::css_parser::splitByToken()
{
	string tempToken;


	int i = 0;
	for (auto& symbol : code)
	{

		if (isSplitSymbol(symbol))
		{
			if (symbol == '.' && i != 0)
			{
				char symb = code[i - 1];
				if (symb >= '0' && symb <= '9')
				{
					tempToken += symbol;
					i++;

					continue;
				}
			}

			if (!tempToken.empty())
			{
				tokens.push_back(tempToken);
				tempToken.clear();
			}

			string symbolToken;
			symbolToken += symbol;

			tokens.push_back(symbolToken);

			i++;
			continue;
		}

		tempToken += symbol;
		i++;
	}



}

void CSS::css_parser::syntaxParseOneBlock(vector<string>& block)
{
	State nowState = State::START_PARSE;

	int countAttributesWithoutValue = 0;

	

	string idOrClassName;

	string attribute;
	string value;
	string pseudo;


	css_block block_css;
	css_block_state block_css_state(true);


	

	for (auto& token : block)
	{
		TokenType nowTokenType = whatIsToken(token);


		switch (nowTokenType)
		{
		case TokenType::ID_SIGN:
		{
			if (nowState == State::NEXT_TOKEN_IS_VALUE)
			{
				nowState = State::NEXT_TOKEN_IS_VALUE;
			}
			else
			{
				nowState = State::NEXT_TOKEN_IS_ID;

				idOrClassName += "#";
			}



			break;
		}

		case TokenType::CLASSNAME_SIGN:
		{
			if (nowState == State::NEXT_TOKEN_IS_VALUE)
			{
				nowState = State::NEXT_TOKEN_IS_VALUE;
			}
			else
			{
				nowState = State::NEXT_TOKEN_IS_CLASSNAME;

				idOrClassName += ".";

			}
			break;
		}

		case TokenType::COLON:
		{
			if (nowState == State::NEXT_TOKEN_IS_ID || nowState == State::NEXT_TOKEN_IS_CLASSNAME)
			{
				nowState = State::NEXT_TOKEN_IS_PSEUDO;
			}
			else
			{
				nowState = State::NEXT_TOKEN_IS_VALUE;
			}

			
			break;
		}

		case TokenType::SEMICOLON:
		{
			if (countAttributesWithoutValue != 0)
			{
				cout << "ERROR: Attribute without value!" << endl;
				return;
			}

			if (attribute.find("color") != -1)
			{
				value = '#' + value;
			}


			block_css_state.set(attribute, CSS::css_attribute::get(attribute, value));

		
			nowState = State::NEXT_TOKEN_IS_ATTRIBUTE;
			break;
		}

		case TokenType::LBRA:
		{
			nowState = State::NEXT_TOKEN_IS_ATTRIBUTE;

			block_css.name(idOrClassName);

			cout << "Start block" << endl;
			break;
		}

		case TokenType::RBRA:
		{
			nowState = State::END_BLOCK;

			cout << "End block" << endl;

			
			// create style set

			//int cl22 = std::get<int>(datas["margin-left"]);

			if (pseudo == "hover")
			{
				block_css.hover(block_css_state);
			}
			else if (pseudo == "active")
			{
				block_css.active(block_css_state);
			}
			else
			{
				block_css.normal(block_css_state);
			}

			if (css_blocks.find(idOrClassName) != css_blocks.end())
			{
				css_blocks[idOrClassName].mergeWith(block_css);

			}
			else
			{
				css_blocks.insert(std::make_pair(idOrClassName, block_css));
			}

			break;
		}

		case TokenType::FIELD:
		{
			switch (nowState)
			{
			case NEXT_TOKEN_IS_ID:
			{
				cout << "This token is ID: " << token << endl;

				idOrClassName += token;

				cout << "Block: " << idOrClassName << endl;

				break;
			}

			case NEXT_TOKEN_IS_CLASSNAME:
			{
				cout << "This token is CLASSNAME: " << token << endl;

				idOrClassName += token;

				cout << "Block: " << idOrClassName << endl;

				break;
			}

			case NEXT_TOKEN_IS_ATTRIBUTE:
			{
				countAttributesWithoutValue++;

				cout << "This token is ATTRIBUTE: " << token << endl;

				attribute.clear();
				attribute = token;

				break;
			}

			case NEXT_TOKEN_IS_VALUE:
			{
				countAttributesWithoutValue--;

				cout << "This token is VALUE: " << token << endl;

				value.clear();
				value = token;

				break;
			}

			case NEXT_TOKEN_IS_PSEUDO:
			{
				cout << "This token is PSEUDO: " << token << endl;

				if (token != "hover" && token != "active" && token != "focus")
				{
					cout << "ERROR: Undefined pseudo class " << token << "!" << endl;

					return;
				}

				pseudo = token;

				break;
			}


			default:
			{
				cout << "ERROR: Undefined token: " << token << endl;
				break;
			}
			}


			break;
		}

		default:break;
		}


	}

	
}

void CSS::css_parser::syntaxParse()
{
	for (auto& block : blocks)
	{
		syntaxParseOneBlock(block);
	}
}

void CSS::css_parser::mergeStyleComponent()
{
	for (auto& block : css_blocks)
	{
		block.second.hover().mergeWithBaseIs(block.second.normal());
		block.second.active().mergeWithBaseIs(block.second.hover());
	}
}
void CSS::css_parser::updateCSS()
{
	for (auto& block : css_blocks)
	{
		cssPlace->add(block.second);
	}
}
//
//map<string, Styles*> CSS::css_parser::getReadyStyles()
//{
//	return resultStyles;
//}