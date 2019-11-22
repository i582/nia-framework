#include "text_line.h"
#include "text.h"

nia::TextLine::TextLine(Text2* parent, string text)
{
	this->parent = parent;
	this->text = text;

	this->isSelect = false;
	this->startCursorSelect;
	this->endCursorSelect;

	setup_token_types();
	setup();
	render();
}

nia::TextLine::~TextLine()
{
	SDL_DestroyTexture(texture);
}

void nia::TextLine::deleteSelected()
{
	this->startCursorSelect = { 0, 0 };
	this->endCursorSelect = { 0, 0 };
}

void nia::TextLine::setup()
{
	// calculate size
	TTF_SizeUTF8(parent->fontTTF, text.c_str(), &size.w, &size.h);
	size.h *= parent->lineHeight;

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTexture(parent->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.w, size.h);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	splitByToken();
}

void nia::TextLine::render()
{
	SDL_SetRenderTarget(parent->renderer, texture);
	SDL_SetRenderDrawColor(parent->renderer, 0x33, 0x33, 0x33, 0xff);
	SDL_RenderClear(parent->renderer);


	// рисуем выделение
	SDL_SetRenderDrawColor(parent->renderer, 0x3b, 0x49, 0x47, 0xff);

	SDL_Rect selectedRect = { 0, 0, 0, size.h };

	int startSelect = std::_Min_value(startCursorSelect.x, endCursorSelect.x);
	int endSelect = std::_Max_value(startCursorSelect.x, endCursorSelect.x);

	TTF_SizeUTF8(parent->fontTTF, text.substr(0, startSelect).c_str(), &selectedRect.x, nullptr);	TTF_SizeUTF8(parent->fontTTF, text.substr(startSelect, abs(startSelect - endSelect)).c_str(), &selectedRect.w, nullptr);

	SDL_RenderFillRect(parent->renderer, &selectedRect);

	int x_shift = 0;

	for (auto& word : words)
	{
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(parent->fontTTF, word.text.c_str(), word.color.colorSDL());
		if (textSurface == nullptr)
			continue;


		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(parent->renderer, textSurface);

		SDL_Rect copyRect = { x_shift, (parent->fontSize * parent->lineHeight - parent->fontSize) / 2, textSurface->w, textSurface->h };
		SDL_RenderCopy(parent->renderer, textTexture, NULL, &copyRect);

		x_shift += textSurface->w;

		SDL_DestroyTexture(textTexture);
		SDL_FreeSurface(textSurface);
	}

	

	SDL_SetRenderTarget(parent->renderer, parent->texture);
}

void nia::TextLine::splitByToken()
{
	string tempToken;
	tokens.clear();

	int i = 0;

	int count_quotes = 0;
	bool first_quotes = true;

	bool in_quotes = false;

	for (auto& symbol : text)
	{
		if (in_quotes)
		{
			if (symbol == '"')
			{
				if (!tempToken.empty())
				{
					tokens.push_back(tempToken);
					tempToken.clear();
				}

				in_quotes = false;
			}

		}
		else if (symbol == '"')
		{
			in_quotes = true;
		}
		else if (isSplitSymbol(symbol))
		{
			
			
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

	if (!tempToken.empty())
	{
		tokens.push_back(tempToken);
		tempToken.clear();
	}


	colorize();
}

bool nia::TextLine::isSplitSymbol(char symbol)
{
	return operators.find(symbol) != -1;
}

nia::TokenType nia::TextLine::whatIsToken(string token)
{ 
	if (Utils::is_number(token))
	{
		return TokenType::NUMBER;
	}

	if (token[0] == '"' || token[0] == '\'')
	{
		return TokenType::QUOTES;
	}

	if (keyword.find(token + " ") != -1)
	{
		return TokenType::KEYWORD;
	}

	if (operators.find(token + " ") != -1)
	{
		return TokenType::OPERATOR;
	}

	
	return TokenType::TEXT;
}

void nia::TextLine::colorize()
{
	words.clear();

	for (auto& token : tokens)
	{
		TokenType type = whatIsToken(token);

		switch (type)
		{
		case nia::TokenType::TEXT:
		{
			words.push_back(Word(token, 0xC8C8C8ff));
			break;
		}

		case nia::TokenType::KEYWORD:
		{
			words.push_back(Word(token, 0xEFC57Dff));
			break;
		}

		case nia::TokenType::OPERATOR:
		{
			words.push_back(Word(token, 0xDFDFBFff));
			break;
		}

		case nia::TokenType::NUMBER:
		{
			words.push_back(Word(token, 0x5B8EBEff));
			break;
		}

		case nia::TokenType::QUOTES:
		{
			words.push_back(Word(token, 0xDFAF8Fff));
			break;
		}
		
		default:break;
		}

		

	}
}

void nia::TextLine::setup_token_types()
{
	
	keyword += "class struct public private protected static virtual override this friend ";
	keyword += "int bool double float char usigned long void const ";
	keyword += "for while do break continue switch case default return if else ";
	keyword += "using namespace ";
	keyword += "true false ";
	keyword += "try catch throw";

	
	operators += "< > = | & : ; , + - ! * / % ( ) [ ] { } ";

	quotes += "\" ' ";

}

void nia::TextLine::setText(string text)
{
	this->text = text;
	setup();
	render();
}

void nia::TextLine::addText(string text, int place)
{
	if (place != this->text.length())
	{
		this->text = this->text.substr(0, place) + text + this->text.substr(place, this->text.length() - place);
	}
	else
	{
		this->text += text;
	}

	
	setup();
	render();
}

bool nia::TextLine::removeSymbol(int place)
{
	if (text.length() > 0)
	{
		if (place == 0)
			return false;

		text = text.substr(0, place - 1) + text.substr(place, text.length() - place);

		setup();
		render();
		return false;
	}
	else
	{
		return true;
	}
}

bool nia::TextLine::removeSymbolAfter(int place)
{
	if (place < text.length())
	{
		text = text.substr(0, place) + text.substr(place + 1, text.length() - place);

		setup();
		render();
		return false;
	}
	else
	{
		return true;
	}
}
