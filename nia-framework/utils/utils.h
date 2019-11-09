#pragma once

#include "SDL.h"

#include "string"
#include "vector"

using std::string;
using std::vector;

namespace Utils
{
	int to_integer(const string& str);
	double to_double(const string& str);

	/**
	 * @brief Parse the string and calculates the value in pixels
	 * @param str String for parse (must contained px or %)
	 * @param parentValue Value relative to which values ​​containing percentages are calculated
	 * @return Calculated value or -1 if error
	 */
	int parseString(const string& str, int parentValue);


	/**
	 * @brief Split the string by into substring by separator (symbol)
	 * @param str String for split
	 * @param symbol The symbol to split the string into
	 * @return Array of string
	 */
	vector<string>* split(string str, char symbol);
	vector<string>* split(char* str, char symbol);
	

	/**
	 * @brief Splits a string into a substring by any of the delimiters in the pattern string
	 * @param str String for split
	 * @param pattern String containing a set of separators
	 * @param separator Symbol for splitting a pattern string into separate delimiters
	 * @return Array of string
	 */
	vector<string>* split(string str, string pattern, char separator = '\t');



	int SDL_SetRenderColor(SDL_Renderer* renderer, SDL_Color color);
}

