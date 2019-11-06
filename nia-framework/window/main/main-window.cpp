#include "main-window.h"

#include "SDL2_gfxPrimitives.h"
#include "../..//utils/draw.h"
using namespace Utils;

void MainWindow::setup()
{
	__container->append(new Container("cont", { {"400px", "100px"}, {"100px", "100px"} }, "back-in-black highway-to-heaven"));

	ContainerStyleRaw* backStyle = new ContainerStyleRaw();
	backStyle->backgroundColor("#00ff00ff");
	backStyle->hoverBackgroundColor("#00aa00ff");
	Window::addStyle("back-in-black", backStyle);

	ContainerStyleRaw* highwayStyle = new ContainerStyleRaw();
	highwayStyle->borderColor("#123456ff");
	Window::addStyle("highway-to-heaven", highwayStyle);









	__container->setupContainer();
	Window::handleStyles();
}

void MainWindow::update()
{




	SDL_SetRenderTarget(renderer, NULL);

	SDL_SetRenderColor(renderer, { 0xff, 0xff, 0xff, 0xff });
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderColor(renderer, { 0x3f, 0x3f, 0x46, 0xff });
	SDL_RenderDrawRect(renderer, NULL);



	__container->render();


/*

	Font::root("../nia-framework/fonts/");

	Font& cons = Font::create("consolas");
	Fonts::add(cons);

	Color white("#ffffff");

	Text text(renderer,
		"At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui officia deserunt mollitia animi, id est laborum et dolorum fuga.",
		{ 50, 200, 400, 300 }, Fonts::at("consolas"), 20, white);*/


		//text.render();

	const int R = 100;





	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


	//for (size_t i = 0; i < 10; i++)
	//{
	//	//SDL_SetRenderColor(renderer, { 0xff, 0xff, 0xff, (Uint8)(0xff / (i*5 + 1)) });
	//	Uint8 alpha = (Uint8)(0xff - (0xff * (i / 9.)));
	//	//cout << (int)alpha << endl;
	//	//SDL_SetRenderColor(renderer, { 0xff, 0xff, 0xff, alpha });

	//	//SDL_SetRenderDrawColor(renderer, alpha, 0xff, 0xff, 0xff);

	//	Uint32 color1 = (alpha << 24) | (0xff << 16) | (0xff << 8) | alpha;

	//	Draw::circle(renderer, 200, 100, 50 - i, color1);
	//}

	Color cl("#EAEAEAff");
	Color cl1("#ffffffff");
	/*Draw::arc(renderer, 200, 100, 100, cl1.color(), cl.color(), 3, 20);

	Draw::hline(renderer, 50, 200, 200, cl1.color(), cl.color(), 20);
	Draw::vline(renderer, 300, 50, 100, cl1.color(), cl.color(), 20);*/


	Draw::roundedShadowRectangle(renderer, 50, 50, 300, 400, 10, cl.color(), cl1.color(), 5, 40);

	//Draw::roundedRectangle(renderer, 100, 100, 200, 100, 20, cl.color());

	//aacircleColor(renderer, 200, 100, 51, 0xffffffff);
	//aacircleColor(renderer, 200, 100, 50, 0xffffffff);
	//aacircleColor(renderer, 200, 100, 40, 0xffffffff);

	//Fonts::close();

	SDL_RenderPresent(renderer);
	
}


void MainWindow::onEvent(SDL_Event* e)
{
	//cout << e->window.windowID << endl;
}

void MainWindow::mouseButtonDown(SDL_Event* e)
{
}

void MainWindow::mouseButtonUp(SDL_Event* e)
{
}

void MainWindow::mouseMotion(SDL_Event* e)
{
}

void MainWindow::mouseWheel(SDL_Event* e)
{
}

void MainWindow::keyDown(SDL_Event* e)
{
}

void MainWindow::keyUp(SDL_Event* e)
{
}

void MainWindow::textInput(SDL_Event* e)
{
}
