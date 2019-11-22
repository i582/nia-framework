#include "mwindow.h"

#include "../..//container/textBlock.h"

void MWindow::setup()
{
	include("././style.css");

	$$->append(new Container("main", { "45px", "30px", "100% - 65px", "100% - 50px" }, ".main"));
	$$->append(new Container("left-side", { "0px", "30px", "45px", "100% - 50px" }, ".side-block"));

	Window::getElementById("main")->append(new Container("editor-main", { "0px", "0px", "100%", "1500px" }, ".editor-main"))
		->text()->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean ultrices lorem id malesuada tempor. Praesent nunc mi, faucibus tempor elementum sit amet, finibus sit amet erat. Proin ut sapien eu turpis pharetra ornare a eu ipsum. Integer iaculis justo leo. Quisque ligula lorem, ullamcorper vestibulum commodo quis, congue at tellus. ");

	Window::getElementById("left-side")->append(new Container("settings", { "8px", "100% - 40px", "30px", "30px" }, ".settings"));

	$$->append(new Container("top-side", { "0px", "0px", "100%", "30px" }, ".top-block"));
	$$->append(new Container("bottom-side", { "0px", "100% - 20px", "100%", "20px" }, ".bottom-block"));
	
		
	Window::getElementById("top-side")->append(new Container("item1", { "45px", "0px", "50px", "100%" }, ".menu-item"))
		->text()->setText("Файл");
	Window::getElementById("top-side")->append(new Container("item2", { "95px", "0px", "60px", "100%" }, ".menu-item"))
		->text()->setText("Правка");

	Window::getElementById("top-side")->append(new Container("logo", { "0px", "0px", "30px", "100%" }, ".logo"));

	Window::getElementById("bottom-side")->append(new Container("current-row", { "200px", "0px", "180px", "100%" }, ".current-row-text"))
		->text()->setText("Строка 15, столбец 1");

	Window::getElementById("bottom-side")->append(new Container("current-count-spaces", { "380px", "0px", "100px", "100%" }, ".current-row-text"))
		->text()->setText("Пробелов: 4");

	Window::getElementById("bottom-side")->append(new Container("current-utf8", { "480px", "0px", "50px", "100%" }, ".current-row-text"))
		->text()->setText("UTF-8");

	Window::getElementById("bottom-side")->append(new Container("current-crlf", { "530px", "0px", "40px", "100%" }, ".current-row-text"))
		->text()->setText("CRLF");

}
