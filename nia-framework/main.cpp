#include "nia-app.h"
#include "nia-main-point.h"

#include "font/fonts.h"
#include "text/text.h"
using namespace NIAApp;

int main(int argc, char** argv)
{
	$.addWindow("new window", { {100, 200}, {1200, 500} }, "win1");
	//$.addWindow("also new window", { {600, 700}, {300, 300} }, "win2");

	$.run();


	/*Font::root("../nia-framework/fonts/");

	Font consolas("consolas");

	TTF_Font* font = consolas(12);


	Font& cons = Font::create("consolas");

	cons.at(12);
	cons.at(21);
	cons.at(45);
	cons.at(124);
	
	Fonts::add(cons);

	TTF_Font* cons1 = Fonts::at("consolas").at(12);


	SDL_Renderer* renderer = nullptr;

	Text text(renderer, "Здесь очень много текста....", { 100, 200, 300, 300 }, Fonts::at("consolas"), 12);








	Fonts::close();*/

	return 0;
}

