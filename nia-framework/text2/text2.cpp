#include "text.h"

nia::Text2::Text2(SDL_Renderer* renderer, string text, SimpleRect size, Font* font, size_t fontSize, Color colorFont)
{
	this->renderer = renderer;
	this->size = size;

	this->text = text;
	this->font = font;
	this->fontSize = fontSize;
	this->colorFont = colorFont;
	this->fontTTF = font->at(fontSize);

	this->lineHeight = 1.3;

	this->isSelected = false;
	

	splitByLines();
	setup();
}

nia::Text2::~Text2()
{
	SDL_DestroyTexture(texture);
}

void nia::Text2::splitByLines()
{
	vector<string>* text_lines = Utils::split(text, '\n');
	
	for (auto& line : *text_lines)
	{
		TextLine* new_line = new TextLine(this, line);
		lines.push_back(new_line);
	}
	
	delete text_lines;
}

void nia::Text2::setup()
{
	size.h = lines.size() * fontSize * lineHeight;

	for (auto& line : lines)
	{
		if (line->size.w > size.w)
		{
			size.w = line->size.w;
		}
	}

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.w, size.h);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

}

void nia::Text2::renderCursor()
{
	// calculate cursor position
	int y = cursorPos.y * fontSize * lineHeight;
	int x = 0;

	TTF_SizeUTF8(fontTTF, lines[cursorPos.y]->text.substr(0, cursorPos.x).c_str(), &x, nullptr);

	SDL_Rect cursorRect = { x, y, 1, fontSize*lineHeight };
	SDL_SetRenderDrawColor(renderer, 0xdf, 0xdf, 0xbf, 0xff);
	SDL_RenderFillRect(renderer, &cursorRect);
}

void nia::Text2::handleSelect()
{
	// сбрасываем выделение
	for (auto& line : lines)
	{
		line->deleteSelected();
	}

	CursorPosition tempStartCursorSelect = startCursorSelect;
	CursorPosition tempEndCursorSelect = endCursorSelect;

	if (tempStartCursorSelect.y > tempEndCursorSelect.y)
	{
		std::swap(tempStartCursorSelect, tempEndCursorSelect);
	}

	// первый случай, когда выделение в одной строке
	if (tempStartCursorSelect.y == tempEndCursorSelect.y)
	{
		lines[tempStartCursorSelect.y]->startCursorSelect.x = tempStartCursorSelect.x;
		lines[tempStartCursorSelect.y]->endCursorSelect.x = tempEndCursorSelect.x;
	}
	// второй случай, если выделение в две строки
	else if (tempStartCursorSelect.y == tempEndCursorSelect.y - 1)
	{
		// устанавливаем выделение до конца первой строки
		lines[tempStartCursorSelect.y]->startCursorSelect.x = tempStartCursorSelect.x;
		lines[tempStartCursorSelect.y]->endCursorSelect.x = lines[tempStartCursorSelect.y]->text.size();

		// устанавливаем выделение от начало строки 
		lines[tempEndCursorSelect.y]->startCursorSelect.x = 0;
		lines[tempEndCursorSelect.y]->endCursorSelect.x = tempEndCursorSelect.x;
	}
	else if (tempEndCursorSelect.y - tempStartCursorSelect.y > 1)
	{
		// устанавливаем выделение до конца первой строки
		lines[tempStartCursorSelect.y]->startCursorSelect.x = tempStartCursorSelect.x;
		lines[tempStartCursorSelect.y]->endCursorSelect.x = lines[tempStartCursorSelect.y]->text.size();


		// для всех строк между верхней и нижней ставим выделение всей строки
		for (size_t i = tempStartCursorSelect.y + 1; i < tempEndCursorSelect.y; i++)
		{
			lines[i]->startCursorSelect.x = 0;
			lines[i]->endCursorSelect.x = lines[i]->text.size();
		}


		// устанавливаем выделение от начало строки
		lines[tempEndCursorSelect.y]->startCursorSelect.x = 0;
		lines[tempEndCursorSelect.y]->endCursorSelect.x = tempEndCursorSelect.x;
	}
}

void nia::Text2::deleteSelect()
{
	isSelected = false;

	for (auto& line : lines)
	{
		line->deleteSelected();
	}
}

nia::CursorPosition nia::Text2::whereIsCursor(SimplePoint mouse)
{
	int numberLine = mouse.y / (int)(fontSize * lineHeight);

	if (numberLine > lines.size() - 1)
		numberLine = lines.size() - 1;

	int calcWidth = 0;
	int countSymbol = 0;
	for (auto& symbol : lines[numberLine]->text)
	{
		int widthSymbol = 0;
		char str[2] = { symbol, '\0' };
		TTF_SizeUTF8(fontTTF, str, &widthSymbol, nullptr);

		calcWidth += widthSymbol;
		countSymbol++;

		if (calcWidth > mouse.x)
		{
			int delta = calcWidth - mouse.x;

			if (delta > widthSymbol / 2.)
			{
				countSymbol--;
			}

			break;
		}
	}

	return { countSymbol, numberLine };
}

nia::string nia::Text2::copySelect()
{
	if (isSelected == false)
		return "";

	string result;

	CursorPosition tempStartCursorSelect = startCursorSelect;
	CursorPosition tempEndCursorSelect = endCursorSelect;

	if (tempStartCursorSelect.y > tempEndCursorSelect.y)
	{
		std::swap(tempStartCursorSelect, tempEndCursorSelect);
	}

	// первый случай, когда выделение в одной строке
	if (tempStartCursorSelect.y == tempEndCursorSelect.y)
	{
		int start = tempStartCursorSelect.x;
		int end = tempEndCursorSelect.x;

		if (start > end)
		{
			std::swap(start, end);
		}

		result = lines[tempStartCursorSelect.y]->text.substr(start, end - start);
	}
	// второй случай, если выделение в две строки
	else if (tempStartCursorSelect.y == tempEndCursorSelect.y - 1)
	{
		int start = tempStartCursorSelect.x;
		int end = lines[tempStartCursorSelect.y]->text.size();

		result += lines[tempStartCursorSelect.y]->text.substr(start, end - start) + '\n';



		start = 0;
		end = tempEndCursorSelect.x;

		result += lines[tempEndCursorSelect.y]->text.substr(start, end - start);
	}
	else if (tempEndCursorSelect.y - tempStartCursorSelect.y > 1)
	{
		int start = tempStartCursorSelect.x;
		int end = lines[tempStartCursorSelect.y]->text.size();

		result += lines[tempStartCursorSelect.y]->text.substr(start, end - start) + '\n';


		// копируем полные строки между верхней и нижней строкой
		for (size_t i = tempStartCursorSelect.y + 1; i < tempEndCursorSelect.y; i++)
		{
			start = 0;
			end = lines[i]->text.size();

			result += lines[tempEndCursorSelect.y]->text.substr(start, end) + '\n';
		}


		// копируем от 0 до позиции весь текст с последней строки
		start = 0;
		end = tempEndCursorSelect.x;
		result += lines[tempEndCursorSelect.y]->text.substr(start, end - start);
	}

	return result;
}

void nia::Text2::render()
{
	SDL_SetRenderTarget(renderer, texture);

	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0x00);
	SDL_RenderFillRect(renderer, NULL);

	for (size_t i = 0; i < lines.size(); i++)
	{
		auto& line = lines[i];

		int y = i * fontSize * lineHeight;

		SDL_Rect rect = { 0, y, line->size.w, line->size.h };

		line->render();

		//SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xff);
		//SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderTarget(renderer, texture);
		SDL_RenderCopy(renderer, line->texture, NULL, &rect);
	}

	renderCursor();

	SDL_SetRenderTarget(renderer, NULL);

	SDL_RenderCopy(renderer, texture, NULL, &size.toSdlRect());
}

void nia::Text2::mouseMotion(SDL_Event* e)
{
	if (mousePush == false)
		return;

	SimplePoint mouse = { e->motion.x, e->motion.y };
	mouse.x -= size.x;
	mouse.y -= size.y;

	if (isSelected == false)
	{
		isSelected = true;
		startCursorSelect = endCursorSelect = whereIsCursor(mouse);
	}
	else
	{
		endCursorSelect = cursorPos = whereIsCursor(mouse);
	}

	handleSelect();
}

void nia::Text2::mouseButtonUp(SDL_Event* e)
{
	mousePush = false;
}

void nia::Text2::mouseButtonDown(SDL_Event* e)
{
	mousePush = true;

	SimplePoint mouse = { e->motion.x, e->motion.y };
	mouse.x -= size.x;
	mouse.y -= size.y;

	

	cursorPos = whereIsCursor(mouse);

	// удаляем выделение
	deleteSelect();
}

void nia::Text2::keyDown(SDL_Event* e)
{
	switch (e->key.keysym.sym)
	{

	case SDLK_v:
	{
		if (SDL_GetModState() & KMOD_CTRL)
		{
			string clipboardText = SDL_GetClipboardText();
			lines.at(cursorPos.y)->addText(clipboardText, cursorPos.x);

			cursorPos.x += clipboardText.length();

			setup();
		}

		break;
	}

	case SDLK_c:
	{
		if (SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(copySelect().c_str());
		}

		break;
	}

	case SDLK_RETURN:
	{
		string new_line_text;

		// Если мы находимся посередине строки и переносим на следующую
		if (cursorPos.x != lines[cursorPos.y]->text.length())
		{
			// новая строка равна всей строке после курсора
			new_line_text += lines[cursorPos.y]->text.substr(cursorPos.x, lines[cursorPos.y]->text.length() - cursorPos.x);

			// устанавливаем текущей строке все что до курсора
			lines[cursorPos.y]->setText(lines[cursorPos.y]->text.substr(0, cursorPos.x));
		}
		// если мы в конце строки то строка пустая
		else
		{
			new_line_text = "";
		}

		TextLine* new_line = new TextLine(this, new_line_text);

		lines.insert(lines.begin() + cursorPos.y + 1, new_line);

		cursorPos.x = 0;
		cursorPos.y += 1;

		setup();
		break;
	}

	case SDLK_BACKSPACE:
	{
		bool line_delete = false;

		// удаляем символ перед курсором, если это последний символ и строка пуста, удаляем строку
		if (lines.at(cursorPos.y)->removeSymbol(cursorPos.x) && lines.size() > 1)
		{
			// удаляем строку
			lines.erase(lines.begin() + cursorPos.y);
			line_delete = true;
		}

		if (cursorPos.x > 0)
		{
			cursorPos.x -= 1;
		}
		else
		{
			if (cursorPos.y > 0)
			{
				cursorPos.y -= 1;

				// если мы в начале строки и удаляем последний символ

				// устанавливаем курсор в положение после текста в строке выше
				cursorPos.x = lines[cursorPos.y]->text.size();

				
				// если строка не была удалена, так как не имеет текста
				if (line_delete == false)
				{
					// добавлям то что было в строке, у которой был нажат backspace к строке выше
					lines[cursorPos.y]->setText(lines[cursorPos.y]->text + lines[cursorPos.y + 1]->text);

					// удаляем строку в которой был нажат backspace
					lines.erase(lines.begin() + cursorPos.y + 1);
				}
			
			}
		}

		setup();
		break;
	}

	case SDLK_DELETE:
	{
		// удаляем символ после курсором, если это последний символ и это не последняя строка
		// то добавляем к строке следующую строку
		if (lines.at(cursorPos.y)->removeSymbolAfter(cursorPos.x) && cursorPos.y < lines.size() - 1)
		{
			// устанавливаем текст
			lines.at(cursorPos.y)->setText(lines.at(cursorPos.y)->text + lines.at(cursorPos.y + 1)->text);

			// удаляем следующую строку
			lines.erase(lines.begin() + cursorPos.y + 1);
		}

		

		break;
	}


	case SDLK_LEFT:
	{
		if (cursorPos.x > 0)
		{
			cursorPos.x -= 1;


			if (SDL_GetModState() & KMOD_SHIFT)
			{
				if (isSelected == false)
				{
					// изначально стартовая коррдината равна положению
					// курсора сдвинутого на 1 вправо
					startCursorSelect = cursorPos;
					startCursorSelect.x += 1;

					// конец выделения это всегда текущее положение курсора
					endCursorSelect = cursorPos;

					isSelected = true;
				}
				else
				{
					// устанавливаем конец в положение курсора
					endCursorSelect = cursorPos;
				}

				handleSelect();
			}
			else
			{
				isSelected = false;

				// сбрасываем выделение
				deleteSelect();
			}
		}
		else
		{
			if (cursorPos.y > 0)
			{
				cursorPos.y -= 1;
				cursorPos.x = lines[cursorPos.y]->text.size();

				if (SDL_GetModState() & KMOD_SHIFT)
				{
					// устанавливаем конец в положение курсора
					endCursorSelect = cursorPos;
				}
			}
				
		}

		break;
	}

	case SDLK_RIGHT:
	{
		if (cursorPos.x < lines[cursorPos.y]->text.size())	
		{
			cursorPos.x += 1;

			if (SDL_GetModState() & KMOD_SHIFT)
			{
				if (isSelected == false)
				{
					// изначально стартовая коррдината равна положению
					// курсора сдвинутого на 1 влево
					startCursorSelect = cursorPos;
					startCursorSelect.x -= 1;

					// конец выделения это всегда текущее положение курсора
					endCursorSelect = cursorPos;

					isSelected = true;
				}
				else
				{
					endCursorSelect = cursorPos;
				}

				handleSelect();
			}
			else
			{
				isSelected = false;
				// сбрасываем выделение
				deleteSelect();
			}
		}
		else
		{
			if (cursorPos.y < lines.size() - 1)
			{
				cursorPos.y += 1;
				cursorPos.x = 0;

				if (SDL_GetModState() & KMOD_SHIFT)
				{
					// устанавливаем конец в положение курсора
					endCursorSelect = cursorPos;
				}
				else
				{
					isSelected = false;
					// сбрасываем выделение
					deleteSelect();
				}
			}
		}
		break;
	}

	case SDLK_DOWN:
	{
		// если мы не на последней строке
		if (cursorPos.y < lines.size() - 1)
		{
			// идем на следующую строку
			cursorPos.y += 1;

			// если положение курсора находится в положении которое больше чем 
			// длина строки ниже
			if (cursorPos.x > lines[cursorPos.y]->text.size())
			{
				// устанавливаем курсор в конец
				cursorPos.x = lines[cursorPos.y]->text.size();
			}
		}
		// если мы на последней строке
		else if (cursorPos.y == lines.size() - 1)
		{
			// ставим курсор в конец строки
			cursorPos.x = lines[cursorPos.y]->text.size();
		}



		if (SDL_GetModState() & KMOD_SHIFT)
		{
			if (isSelected == false)
			{
				// изначально стартовая коррдината равна положению курсора
				// сдвинутого на 1 вверх
				startCursorSelect = cursorPos;
				startCursorSelect.y -= 1;
				// конец выделения это всегда текущее положение курсора
				endCursorSelect = cursorPos;

				isSelected = true;
			}
			else
			{
				// устанавливаем конец в положение курсора
				endCursorSelect = cursorPos;
			}

			handleSelect();
		}
		else
		{
			isSelected = false;
			// сбрасываем выделение
			deleteSelect();
		}

		break;
	}

	case SDLK_UP:
	{
		// если мы не на первой строке
		if (cursorPos.y > 0)
		{
			// идем на строку выше
			cursorPos.y -= 1;

			// если положение курсора находится в положении которое больше чем 
			// длина строки выше
			if (cursorPos.x > lines[cursorPos.y]->text.size())
			{
				// устанавливаем курсор в конец
				cursorPos.x = lines[cursorPos.y]->text.size();
			}

		}
		// если мы на первой строке
		else if (cursorPos.y == 0)
		{
			// ставим курсор в начало строки
			cursorPos.x = 0;
		}




		if (SDL_GetModState() & KMOD_SHIFT)
		{
			if (isSelected == false)
			{
				// изначально стартовая коррдината равна положению курсора
				// сдвинутого на 1 вниз
				startCursorSelect = cursorPos;
				startCursorSelect.y += 1;
				// конец выделения это всегда текущее положение курсора
				endCursorSelect = cursorPos;

				isSelected = true;
			}
			else
			{
				// устанавливаем конец в положение курсора
				endCursorSelect = cursorPos;
			}

			handleSelect();
		}
		else
		{
			isSelected = false;
			// сбрасываем выделение
			deleteSelect();
		}

		break;
	}

	default:break;
	}

	render();
}

void nia::Text2::textInput(SDL_Event* e)
{
	lines.at(cursorPos.y)->addText(e->text.text, cursorPos.x);

	cursorPos.x += 1;

	setup();
	render();
}
