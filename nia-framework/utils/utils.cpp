#include "utils.h"

int Utils::to_integer(const string& str)
{
	return stoi(str);
}

double Utils::to_double(const string& str)
{
	return stod(str);
}

int Utils::parseString(const string &str, int parentValue)
{
	int index = 0;
	int result = -1;

	if ((index = str.find("px")) != -1)
	{
		result = Utils::to_integer(str.substr(0, index));
	}
	else if ((index = str.find('%')) != -1)
	{
		result = (int)((Utils::to_integer(str.substr(0, index)) / 100.) * parentValue);
	}

	return result;
}



vector<string>* Utils::split(string str, char symbol)
{
	vector<string>* result = new vector<string>;
	string temp;

	for (size_t i = 0; i < str.length(); i++)
	{
		char current = str[i];

		if (current == symbol)
		{
			result->push_back(temp);
			temp.clear();
		}
		else
		{
			temp += current;
		}
	}

	if (!temp.empty())
		result->push_back(temp);

	return result;
}

vector<string>* Utils::split(char* str, char symbol)
{
	string st_str(str);
	return Utils::split(st_str, symbol);
}

vector<string>* Utils::split(string str, string pattern, char separator)
{
	vector<string>* separators = Utils::split(pattern, separator);
	vector<string>* result = new vector<string>;
	string temp;
	bool is_sep = false;

	for (size_t i = 0; i < str.length(); i++)
	{
		char current = str[i];

		for (auto& separator : *separators)
		{
			if (current == separator[0])
			{
				is_sep = true;
			}
		}

		if (is_sep)
		{
			result->push_back(temp);
			temp.clear();
			is_sep = false;
		}
		else
		{
			temp += current;
		}

	}

	if (!temp.empty())
		result->push_back(temp);

	return result;
}



bool Utils::is_integer(string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str.at(i) < '0' || str.at(i) > '9')
		{
			return false;
		}
	}

	return true;
}

int Utils::SDL_SetRenderColor(SDL_Renderer* renderer, SDL_Color color)
{
	return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
