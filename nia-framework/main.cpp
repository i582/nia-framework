#include "nia-app.h"
#include "nia-main-point.h"

using namespace NIAApp;

int main(int argc, char** argv)
{
	$.addWindow("new window", { {100, 200}, {1200, 500} }, "win1");

	$.run();
	return 0;
}

