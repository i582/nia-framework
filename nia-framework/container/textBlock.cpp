#include "textBlock.h"

void TextBlock::setup()
{

	_text->setText("ыыыы");

	append(new Container("test1", { "0px", "30px", "45px", "100px" }, ".test"));

	cout << "fsfsfs" << endl;
}
