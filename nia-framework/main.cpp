#include "nia-app.h"
#include "nia-main-point.h"

#include "window/main/mwindow.h"

using namespace NIAApp;

int main(int argc, char** argv)
{
	$.addWindow(new MWindow("new window", { {100, 200}, {1200, 500} }));



	$.run();
	return 0;
}

