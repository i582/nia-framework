#include "mwindow.h"

void MWindow::setup()
{
	include("././style.css");


	//$$->append(new Container("cont", { "0px", "0px", "50%", "100%" }, ".container"));

	//$$->append(new Container("#tooltip-1", { "100px", "30px", "425px", "25px" }, ".tooltip"));


	/*Window::getElementById("cont")->append(new Container("cont-3", { "50px", "50px", "220px", "25px" }, ".search-block"));
	Window::getElementById("cont-3")->text()->setText("Поиск в Visual Studio");


	Window::getElementById("#tooltip-1")->text()->setText("E:/Programming/nia-framework/nia-framework/window/main/");*/

	
	$$->append(new Container("main", { "45px", "30px", "100% - 65px", "100% - 50px" }, ".main"));
	$$->append(new Container("left-side", { "0px", "0px", "45px", "100%" }, ".side-block"));


	Window::getElementById("main")->append(new Container("editor-main", { "0px", "0px", "100%", "1500px" }, ".editor-main"))
		->text()->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean ultrices lorem id malesuada tempor. Praesent nunc mi, faucibus tempor elementum sit amet, finibus sit amet erat. Proin ut sapien eu turpis pharetra ornare a eu ipsum. Integer iaculis justo leo. Quisque ligula lorem, ullamcorper vestibulum commodo quis, congue at tellus. ");




	$$->append(new Container("top-side", { "0px", "0px", "100%", "30px" }, ".top-block"));
	$$->append(new Container("bottom-side", { "0px", "100% - 20px", "100%", "20px" }, ".bottom-block"));
		
		
	//Window::getElementById("top-side")->append(new Container("item1", { "30px", "0px", "100px", "100%" }, ".menu-item"))
	//	->text()->setText("Файл");

	Window::getElementById("top-side")->append(new Container("logo", { "0px", "0px", "30px", "100%" }, ".logo"));

	//$$->append(new Container("block", { "50% - 50px", "50% - 50px", "100px", "100px" }, ".side-block"));



}
