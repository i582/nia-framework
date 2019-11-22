#include "main-window.h"


using namespace Utils;

MainWindow::MainWindow(string title, Rect size) : Window(title, size)
{

	Font::root("../nia-framework/fonts/");
	Font font1("consolas");
	text = new nia::Text2(renderer, "Hello World!\nNext line!", { 100, 100, 0, 0 }, &font1, 18, Color(0xffffffff));

}

void MainWindow::update()
{
	if (!wasSetupStyle)
	{
		Window::handleStyles();
		wasSetupStyle = true;
	}

	if (!wasSetupContainer)
	{
		__container->setupContainer();
		wasSetupContainer = true;
	}


	SDL_SetRenderTarget(renderer, NULL);

	SDL_SetRenderColor(renderer, { 0x33, 0x33, 0x33, 0xff });
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderColor(renderer, { 0xff, 0xff, 0xff, 0x00 });
	SDL_RenderDrawRect(renderer, NULL);



	//__container->render();


	text->render();

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

	case SDL_WINDOWEVENT:
	{
		switch (e->window.event)
		{

		case SDL_WINDOWEVENT_RESIZED:
		{
			SDL_Log("Window %d resized to %dx%d",
				e->window.windowID, e->window.data1,
				e->window.data2);

			int newW = e->window.data1;
			int newH = e->window.data2;

			Rect r = { 0, 0, newW, newH };

			__container->setupSize(&r);

			break;

		}
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_Log("Window %d size changed to %dx%d",
				e->window.windowID, e->window.data1,
				e->window.data2);
			break;

		}
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

	text->mouseButtonDown(e);

	update();
}

void MainWindow::mouseButtonUp(SDL_Event* e)
{
	Container* hover = __container->onContainerHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseButtonUp(e);
	}

	__container->update();

	text->mouseButtonUp(e);

	update();
}

void MainWindow::mouseMotion(SDL_Event* e)
{
	Container* hover = __container->onContainerHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseMotion(e);
	}

	__container->update();

	text->mouseMotion(e);

	update();
}

void MainWindow::mouseWheel(SDL_Event* e)
{
	const int scrollDirection = e->wheel.y;

	if (e->motion.x == -1 || e->motion.y == -1 || e->motion.x == 1 || e->motion.y == 1)
	{
		SDL_GetMouseState(&e->motion.x, &e->motion.y);
	}

	Container* hover = __container->onContainerHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseScroll(e, scrollDirection);
	}

	__container->update();
}

void MainWindow::keyDown(SDL_Event* e)
{
	text->keyDown(e);

	update();
}

void MainWindow::keyUp(SDL_Event* e)
{
}

void MainWindow::textInput(SDL_Event* e)
{
	text->textInput(e);

	update();
}
