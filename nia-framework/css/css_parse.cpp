#include "css_parse.h"

CssParse::CssParse(string filePath)
{
	this->filePath = filePath;

	openFile();
	splitByToken();
	splitByBlock();
	syntaxParse();
	mergeStyleComponent();
}

void CssParse::openFile()
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

void CssParse::deleteExcess()
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

bool CssParse::isSplitSymbol(char symbol)
{
	return symbol == ':' || symbol == '.' || symbol == '#' || symbol == ';' || symbol == '{' || symbol == '}';
}

TokenType CssParse::whatIsToken(string token)
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

void CssParse::splitByBlock()
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

void CssParse::splitByToken()
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

void CssParse::syntaxParseOneBlock(vector<string>& block)
{
	State nowState = State::START_PARSE;

	int countAttributesWithoutValue = 0;

	Styles* style = new Styles();
	StyleState styleState;

	string idOrClassName;

	string attribute;
	string value;
	string pseudo;


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

			styleState.set(attribute, value);

			nowState = State::NEXT_TOKEN_IS_ATTRIBUTE;
			break;
		}

		case TokenType::LBRA:
		{
			nowState = State::NEXT_TOKEN_IS_ATTRIBUTE;

			cout << "Start block" << endl;
			break;
		}

		case TokenType::RBRA:
		{
			nowState = State::END_BLOCK;

			cout << "End block" << endl;


			// create style set

			if (pseudo == "hover")
			{
				style->_hover = styleState;
			}
			else if (pseudo == "active")
			{
				style->_active = styleState;
			}
			else
			{
				style->_normal = styleState;
			}

			if (resultStyles.find(idOrClassName) != resultStyles.end())
			{
				style->mergeTo(resultStyles[idOrClassName]);

			}
			else
			{
				resultStyles.insert(std::make_pair(idOrClassName, style));
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

void CssParse::syntaxParse()
{
	for (auto& block : blocks)
	{
		syntaxParseOneBlock(block);
	}
}

void CssParse::mergeStyleComponent()
{
	for (auto& style : resultStyles)
	{
		style.second->_hover.mergeWith(style.second->_normal);
		style.second->_active.mergeWith(style.second->_hover);
	}
}

map<string, Styles*> CssParse::getReadyStyles()
{
	return resultStyles;
}
