#include "mwindow.h"

void MWindow::setup()
{
	include("././style.css");


	//$$->append(new Container("cont", { "0px", "0px", "50%", "100%" }, ".container"));

	//$$->append(new Container("#tooltip-1", { "100px", "30px", "425px", "25px" }, ".tooltip"));


	/*Window::getElementById("cont")->append(new Container("cont-3", { "50px", "50px", "220px", "25px" }, ".search-block"));
	Window::getElementById("cont-3")->text()->setText("Поиск в Visual Studio");


	Window::getElementById("#tooltip-1")->text()->setText("E:/Programming/nia-framework/nia-framework/window/main/");*/

	

	/*$$->append(new Container("left-side", { "0px", "0px", "50px", "100%" }, ".side-block"));

	$$->append(new Container("main", { "50px", "0px", "100% - 50px", "100%" }, ".main"));*/


	$$->append(new Container("block", { "50% - 50px", "50% - 50px", "100px", "100px" }, ".side-block"));


	Window::getElementById("block")->addEventListener("click", lambda(Container * caller, Event * e)
	{
		cout << "Hello World!" << endl;
	});

}
