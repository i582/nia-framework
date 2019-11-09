#include "style-state.h"

StyleState::StyleState()
{
	colors["background"] = "none";
	colors["border"] = "none";
	colors["text"] = "none";

	text["font-family"] = "none";
	text["font-size"] = "none";
	
	text["line-height"] = "none";
	text["text-align"] = "none";

	text["vertical-align"] = "none";
	text["horizontal-align"] = "none";
}

StyleState::StyleState(bool generalSetup)
{
	colors["background"] = "#ffffff";
	colors["border"] = "#ffffff00";
	colors["text"] = "#000000";

	text["font-family"] = "consolas";
	text["font-size"] = "14px";

	text["line-height"] = "1.2";
	text["text-align"] = "left";

	text["vertical-align"] = "top";
	text["horizontal-align"] = "left";
}

StyleState* StyleState::setColor(string key, string value)
{
	colors[key] = value;
	return this;
}

StyleState* StyleState::setTextStyle(string key, string value)
{
	text[key] = value;
	return this;
}

StyleState* StyleState::merge(StyleState* style)
{
	for (auto& color : colors)
	{
		if (color.second != "none")
		{
			style->colors[color.first] = color.second;
		}
	}

	for (auto& textStyle : text)
	{
		if (textStyle.second != "none")
		{
			style->text[textStyle.first] = textStyle.second;
		}
	}

	return this;
}

int StyleState::getInt(string key)
{
	if (key == "font-size")
	{
		return std::stoi(text[key]);
	}
}

double StyleState::getDouble(string key)
{
	if (key == "line-height")
	{
		return std::stod(text[key]);
	}
}

string StyleState::getString(string key)
{
	if (key == "font-family" || key == "text-align" || key == "vertical-align" || key == "horizontal-align")
	{
		return text[key];
	}
}

Color StyleState::getColor(string key)
{
	if (key == "background" || key == "border" || key == "text")
	{
		return Color(colors[key]);
	}
}
