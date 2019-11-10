#include "style-state.h"

StyleState::StyleState()
{
	styles["background-color"] = "none";
	styles["border-color"] = "none";
	styles["text-color"] = "none";

	styles["font-family"] = "none";
	styles["font-size"] = "none";
	
	styles["line-height"] = "none";
	styles["text-align"] = "none";

	styles["vertical-align"] = "none";
	styles["horizontal-align"] = "none";

	styles["margin-top"] = "none";
	styles["margin-bottom"] = "none";

	styles["margin-left"] = "none";
	styles["margin-right"] = "none";


	styles["radius"] = "none";
}

StyleState::StyleState(bool generalSetup)
{
	styles["background-color"] = "#ffffff";
	styles["border-color"] = "#ffffff00";
	styles["text-color"] = "#000000";

	styles["font-family"] = "consolas";
	styles["font-size"] = "14px";

	styles["line-height"] = "1.2";
	styles["text-align"] = "left";

	styles["vertical-align"] = "top";
	styles["horizontal-align"] = "left";

	styles["margin-top"] = "0px";
	styles["margin-bottom"] = "0px";

	styles["margin-left"] = "0px";
	styles["margin-right"] = "0px";

	styles["radius"] = "0px";
}

StyleState* StyleState::set(string key, string value)
{
	styles[key] = value;
	return this;
}

StyleState* StyleState::mergeTo(StyleState* styleState)
{
	for (auto& style : styles)
	{
		if (style.second != "none")
		{
			styleState->styles[style.first] = style.second;
		}
	}

	return this;
}

StyleState* StyleState::mergeWith(StyleState styleState)
{
	for (auto& style : styles)
	{
		if (style.second != "none")
		{
			styleState.styles[style.first] = style.second;
		}
	}

	styles = styleState.styles;

	return this;
}

int StyleState::getInt(string key)
{
	if (key == "font-size" || key == "margin-top" || key == "margin-bottom" || key == "margin-left" || key == "margin-right")
	{
		return std::stoi(styles[key]);
	}
	else if (key == "radius")
	{
		return std::stoi(styles[key]);
	}
}
	
double StyleState::getDouble(string key)
{
	if (key == "line-height")
	{
		return std::stod(styles[key]);
	}
}

string StyleState::getString(string key)
{
	if (key == "font-family" || key == "text-align" || key == "vertical-align" || key == "horizontal-align")
	{
		return styles[key];
	}
}

Color StyleState::getColor(string key)
{
	if (key == "background-color" || key == "border-color" || key == "color")
	{
		return Color(styles[key]);
	}
	else
	{
		cout << "ERROR: " << key << " is not set as Color field" << endl;
		return Color("#ff00ff");
	}
}
