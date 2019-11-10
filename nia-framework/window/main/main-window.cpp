#include "main-window.h"

#include "SDL2_gfxPrimitives.h"
#include "../..//utils/draw.h"


#include "../../css/css_parse.h"

using namespace Utils;

void MainWindow::setup()
{
	CssParse parse("././style.css");
	Window::__containersStyles = parse.getReadyStyles();

	__container->append(new Container("cont", { "0px", "0px", "50%", "100%" }, ".container"));

	__container->append(new Container("cont-1", { "0px", "60%", "40%", "100%" }, "con1"));

	//Window::getElementById("cont")->append(new Container("cont-child", { {"12%", "12%"}, {"75%", "150%"} }, "back-in-black hoverss"));
	
	//Window::getElementById("cont-child")->append(new Container("cont-child-1", { {"12%", "12%"}, {"75%", "150%"} }, "yellow hoverss"));
	

	//Color textColor("#ff00ff");

	//Window::getElementById("cont-child-1")->text()->setText("Hello World! It's new Text! Целью данной работы является создание класса «строка» и производных классов от него, а также разработка интерфейса для ввода начальных значений, отображения результатов и тестирования методов классов.");
	//Window::getElementById("cont-child-1")->text()->set(textColor);

	Window::getElementById("cont")->text()->setText("Hello World! It's new Text! Целью данной работы является создание класса «строка» и производных классов от него, а также разработка интерфейса для ввода начальных значений, отображения результатов и тестирования методов классов.");


	//Window::getElementById("cont-1")->text()->setText("Hello World! It's new Text! Целью данной работы является создание класса «строка» и производных классов от него, а также разработка интерфейса для ввода начальных значений, отображения результатов и тестирования методов классов.");


	Window::getElementById("cont-1")->append(new Container("cont-3", { "50px", "50px", "220px", "25px" }, ".search-block"));

	Window::getElementById("cont-1")->append(new Container("cont-name", { "49px", "290px", "100px", "27px" }, "project-name"));



	Window::getElementById("cont-3")->text()->setText("Поиск в Visual Studio");
	Window::getElementById("cont-name")->text()->setText("nia-framework");

	Window::getElementById("cont-3")->addEventListener("click", lambda(Container* sender, Event* e)
	{
		sender->toggleClass("color-blue");
	});


	Styles* projName = new Styles(true);

	projName->normal()->set("background-color", "#252526");
	projName->hover()->set("background-color", "#252526");

	projName->normal()->set("color", "#ffffff");
	projName->hover()->set("color", "#ffffff");

	projName->normal()->set("text-align", "center");
	projName->hover()->set("text-align", "center");

	projName->normal()->set("vertical-align", "center");
	projName->hover()->set("vertical-align", "center");

	projName->normal()->set("font-size", "12px");
	projName->hover()->set("font-size", "12px");

	projName->normal()->set("line-height", "1");
	projName->hover()->set("line-height", "1");

	Window::addStyle("project-name", projName);


	Styles* colorBlue = new Styles();

	colorBlue->normal()->set("text", "#007ACC");
	colorBlue->hover()->set("text", "#007ACC");

	Window::addStyle("color-blue", colorBlue);
	


	Styles* con3 = new Styles(true);

	con3->normal()->set("background-color", "#333337");
	con3->hover()->set("background-color", "#333337");

	con3->normal()->set("color", "#999999");
	con3->hover()->set("color", "#ffffff");

	con3->normal()->set("border-color", "#3F3F46");
	con3->hover()->set("border-color", "#007ACC");

	//con1->normal()->set("margin-top", "50px");
	//con3->normal()->set("margin-left", "50px");
	//con3->normal()->set("vertical-align", "center");
	/*raw->hover()->set("background-color", "#123456");*/

	/*raw->normal()->set("text", "#ffffff");
	raw->hover()->set("text", "#ffffff");*/

	/*raw->normal()->set("line-height", "1.5");
	raw->hover()->set("line-height", "1.7");*/


	con3->normal()->set("text-align", "left");
	con3->hover()->set("text-align", "left");

	con3->normal()->set("margin-left", "6px");
	con3->hover()->set("margin-left", "6px");
	
	con3->normal()->set("font-size", "13px");
	con3->hover()->set("font-size", "13px");

	con3->normal()->set("line-height", "1");
	con3->hover()->set("line-height", "1");

	con3->normal()->set("vertical-align", "center");
	con3->hover()->set("vertical-align", "center");

	/*con1->normal()->set("vertical-align", "center");
	con1->hover()->set("vertical-align", "bottom");*/
	//raw->hover()->set("font-size", "18px");


	/*con3->normal()->set("radius", "7px");
	con3->hover()->set("radius", "7px");*/

	Window::addStyle("button", con3);




	Styles* raw = new Styles(true);

	/*raw->normal()->set("background-color", "#123456");
	raw->hover()->set("background-color", "#123456");*/

	/*raw->normal()->set("text", "#ffffff");
	raw->hover()->set("text", "#ffffff");*/

	/*raw->normal()->set("line-height", "1.5");
	raw->hover()->set("line-height", "1.7");*/

	raw->normal()->set("background-color", "#cccccc");
	raw->hover()->set("background-color", "#dddddd");

	raw->normal()->set("color", "#000000");
	raw->hover()->set("color", "#000000");


	raw->normal()->set("text-align", "center");
	raw->hover()->set("text-align", "right");

	raw->normal()->set("vertical-align", "center");
	raw->hover()->set("vertical-align", "bottom");

	raw->normal()->set("margin-top", "50px");

	//raw->hover()->set("font-size", "18px");

	Window::addStyle("hoverss", raw);


	Styles* con1 = new Styles(true);

	con1->normal()->set("background-color", "#2D2D30");
	con1->hover()->set("background-color", "#2D2D30");

	con1->normal()->set("color", "#ffffff");
	con1->hover()->set("color", "#ffffff");
	
	//con1->normal()->set("margin-top", "50px");
	con1->normal()->set("margin-left", "50px");
	con1->normal()->set("vertical-align", "center");
	/*raw->hover()->set("background-color", "#123456");*/

	/*raw->normal()->set("text", "#ffffff");
	raw->hover()->set("text", "#ffffff");*/

	/*raw->normal()->set("line-height", "1.5");
	raw->hover()->set("line-height", "1.7");*/


	con1->normal()->set("text-align", "left");
	con1->hover()->set("text-align", "left");

	con1->normal()->set("radius", "20px");
	con1->hover()->set("radius", "20px");
	/*con1->normal()->set("vertical-align", "center");
	con1->hover()->set("vertical-align", "bottom");*/
	//raw->hover()->set("font-size", "18px");

	Window::addStyle("con1", con1);

/*
	Styles* raw1 = new Styles();

	raw->normal().set("border", "#654321");

	raw->mergeTo(raw1);*/

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
