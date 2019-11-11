#include "mwindow.h"

void MWindow::setup()
{
	include("././style.css");


	__container->append(new Container("cont", { "0px", "0px", "50%", "100%" }, ".container"));

	__container->append(new Container("#tooltip-1", { "100px", "30px", "425px", "25px" }, ".tooltip"));


	Window::getElementById("cont")->append(new Container("cont-3", { "50px", "50px", "220px", "25px" }, ".search-block"));
	Window::getElementById("cont-3")->text()->setText("Поиск в Visual Studio");


	Window::getElementById("#tooltip-1")->text()->setText("E:/Programming/nia-framework/nia-framework/window/main/");
}
