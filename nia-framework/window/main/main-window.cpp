#include "main-window.h"

#include "SDL2_gfxPrimitives.h"
#include "../..//utils/draw.h"



using namespace Utils;

void MainWindow::setup()
{
	__container->append(new Container("cont", { "0px", "0px", "90%", "100%" }, "back-in-black highway-to-heaven"));

	Window::getElementById("cont")->append(new Container("cont-child", { {"12%", "12%"}, {"75%", "150%"} }, "back-in-black hoverss"));
	
	Window::getElementById("cont-child")->append(new Container("cont-child-1", { {"12%", "12%"}, {"75%", "150%"} }, "yellow hoverss"));
	

	Color textColor("#ff00ff");

	Window::getElementById("cont-child-1")->text()->setText("Hello World! It's new Text! Целью данной работы является создание класса «строка» и производных классов от него, а также разработка интерфейса для ввода начальных значений, отображения результатов и тестирования методов классов.");
	//Window::getElementById("cont-child-1")->text()->setColor(textColor);


	//Style* backStyle = new Style();
	//backStyle->backgroundColor("#ddddddff");
	//backStyle->hoverBackgroundColor("#00aa00ff");

	//backStyle->borderColor("#ff00ff");
	//backStyle->hoverBorderColor("#0000ff");
	//backStyle->activeBorderColor("#00ffff");
	//backStyle->textSize("25px");
	//backStyle->textColor("#ff00ff");
	//backStyle->hoverTextColor("#0000ff");

	////backStyle->shadow("0px 5px #dddddd #ffffff");
	//Window::addStyle("back-in-black", backStyle);

	//Style* hStyle = new Style();
	//hStyle->backgroundColor("#cccccc");
	//Window::addStyle("highway-to-heaven", hStyle);

	//Style* shStyle = new Style();
	////shStyle->shadow("0px 5px #dddddd #ffffff");
	//Window::addStyle("shadow", shStyle);

	//Style* yellowStyle = new Style();
	//yellowStyle->backgroundColor("#ffff00");
	//yellowStyle->hoverBackgroundColor("#aaee00");
	//yellowStyle->textLineHeight("1.6");
	//Window::addStyle("yellow", yellowStyle);


	//Style* mainStyle = new Style();
	//mainStyle->backgroundColor("#ffffff");
	//Window::addStyle("main", mainStyle);

	//__container->addClass("main");




	Styles* raw = new Styles(true);

	raw->normal()->setColor("background", "#123456");
	raw->hover()->setColor("background", "#123456");

	raw->normal()->setColor("text", "#ffffff");
	raw->hover()->setColor("text", "#ffffff");

	raw->normal()->setTextStyle("line-height", "1.5");
	raw->hover()->setTextStyle("line-height", "1.7");

	//raw->hover()->setTextStyle("font-size", "18px");

	Window::addStyle("hoverss", raw);

/*
	Styles* raw1 = new Styles();

	raw->normal().setColor("border", "#654321");

	raw->merge(raw1);*/

/*
	Window::getElementById("cont-child")->addEventListener("onmouseover", [=](Container* sender, Event* e)
	{
		cout << "Mouse over cont-chld" << endl;
	});

	Window::getElementById("cont-child")->addEventListener("onmouseout", [=](Container* sender, Event* e)
	{
		cout << "Mouse out cont-chld" << endl;
	});

	Window::getElementById("cont-child-1")->addEventListener("hover", [=](Container* sender, Event* e)
	{
		cout << "Click cont-chld-1" << endl;
	});

*/

	Window::getElementsByClassName("back-in-black")->addEventListener("click", lambda(Container* sender, Event* e)
	{
		cout << "Click by " << sender->id() << endl;
	});

	Window::getElementsByClassName("back-in-black")->each(lambda(Container* sender)
	{
		cout << "Container with id " << sender->id() << endl;
	});


	Window::handleStyles();
	__container->setupContainer();
}

void MainWindow::update()
{
	SDL_SetRenderTarget(renderer, NULL);

	SDL_SetRenderColor(renderer, { 0xff, 0xff, 0xff, 0xff });
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderColor(renderer, { 0x3f, 0x3f, 0x46, 0xff });
	SDL_RenderDrawRect(renderer, NULL);


	

	__container->render();

	SDL_SetRenderColor(renderer, { 0x3f, 0x3f, 0x46, 0xff });
	SDL_Point p = { 5200, 250 };
	SDL_RenderDrawPoint(renderer, 520, 250);
/*

	Font::root("../nia-framework/fonts/");

	Font& cons = Font::create("consolas");
	Fonts::add(cons);

	Color white("#ffffff");

	Text text(renderer,
		"At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui officia deserunt mollitia animi, id est laborum et dolorum fuga.",
		{ 50, 200, 400, 300 }, Fonts::at("consolas"), 20, white);*/


		//text.render();

	//const int R = 100;





	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


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

	//Color cl("#EAEAEAff");
	//Color cl1("#ffffffff");
	/*Draw::arc(renderer, 200, 100, 100, cl1.color(), cl.color(), 3, 20);

	Draw::hline(renderer, 50, 200, 200, cl1.color(), cl.color(), 20);
	Draw::vline(renderer, 300, 50, 100, cl1.color(), cl.color(), 20);*/


	//Draw::roundedShadowRectangle(renderer, 50, 50, 300, 400, 10, cl.color(), cl1.color(), 5, 40);

	//Draw::roundedRectangle(renderer, 100, 100, 200, 100, 20, cl.color());

	//aacircleColor(renderer, 200, 100, 51, 0xffffffff);
	//aacircleColor(renderer, 200, 100, 50, 0xffffffff);
	//aacircleColor(renderer, 200, 100, 40, 0xffffffff);

	//Fonts::close();

	SDL_RenderPresent(renderer);
	
}


void MainWindow::onEvent(SDL_Event* e)
{
	switch (e->type)
	{

	case SDL_MOUSEMOTION:
	{
		mouseMotion(e);
		break;
	}

	case SDL_MOUSEBUTTONDOWN:
	{
		mouseButtonDown(e);
		break;
	}

	case SDL_MOUSEBUTTONUP:
	{
		mouseButtonUp(e);
		break;
	}

	case SDL_MOUSEWHEEL:
	{
		mouseWheel(e);
		break;
	}

	case SDL_KEYDOWN:
	{
		keyDown(e);
		break;
	}

	case SDL_KEYUP:
	{
		keyUp(e);
		break;
	}

	case SDL_TEXTINPUT:
	{
		textInput(e);
		break;
	}

	break;
	}
}

void MainWindow::mouseButtonDown(SDL_Event* e)
{
	Container* hover = __container->onContainerHover({e->motion.x, e->motion.y});

	if (hover != nullptr)
	{
		hover->mouseButtonDown(e);
	}
	
	__container->update();
}

void MainWindow::mouseButtonUp(SDL_Event* e)
{
	Container* hover = __container->onContainerHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseButtonUp(e);
	}

	__container->update();
}

void MainWindow::mouseMotion(SDL_Event* e)
{
	Container* hover = __container->onContainerHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseMotion(e);
	}

	__container->update();
}

void MainWindow::mouseWheel(SDL_Event* e)
{
	int scroolDirection = e->wheel.y;

	if (e->motion.x == -1 || e->motion.y == -1 || e->motion.x == 1 || e->motion.y == 1)
	{
		SDL_GetMouseState(&e->motion.x, &e->motion.y);
	}

	Container* hover = __container->onContainerHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseScroll(e, scroolDirection);
	}

	__container->update();
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
