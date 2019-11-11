#include "main-window.h"

#include "SDL2_gfxPrimitives.h"
#include "../..//utils/draw.h"


using namespace Utils;

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

	SDL_SetRenderColor(renderer, { 0xff, 0xff, 0xff, 0x00 });
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderColor(renderer, { 0xff, 0xff, 0xff, 0x00 });
	SDL_RenderDrawRect(renderer, NULL);



	__container->render();

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
