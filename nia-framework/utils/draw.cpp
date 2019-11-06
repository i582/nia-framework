#include "draw.h"

void Draw::circle(SDL_Renderer* renderer, int x, int y, int r, Uint32 color)
{
	Uint8* c = (Uint8*)& color;
	SDL_SetRenderDrawColor(renderer, c[3], c[2], c[1], c[0]);

	double n = 0;
	double x1, y1;

	while (n <= 2 * M_PI)
	{
		n = n + M_PI / 1000;
		x1 = round(r * cos(n));
		y1 = round(r * sin(n));

		SDL_RenderDrawPoint(renderer, x + x1, y + y1);
	}
}

void Draw::circle(SDL_Renderer* renderer, int x, int y, int r, Uint32 color, size_t thickness)
{
	for (size_t i = 0; i < thickness; i++)
	{
		circle(renderer, x, y, r + i, color);
	}
}

void Draw::circle(SDL_Renderer* renderer, int x, int y, int r, Uint32 start_color, Uint32 end_color, size_t thickness)
{
	Uint8* sc = (Uint8*)& start_color;
	Uint8* ec = (Uint8*)& end_color;

	

	int dr = sc[3] - ec[3];
	int dg = sc[2] - ec[2];
	int db = sc[1] - ec[1];
	int da = sc[0] - ec[0];


	for (size_t i = 0; i < thickness; i++)
	{
		double progress = i / (double)thickness;

		Uint32 temp_color = start_color;
		Uint8* tc = (Uint8*)& temp_color;
		
		tc[3] -= progress * dr;
		tc[2] -= progress * dg;
		tc[1] -= progress * db;
		tc[0] -= progress * da;

		Uint32 result_color = *(Uint32*)tc;

		circle(renderer, x, y, r + i, result_color);
	}

	//aacircleColor(renderer, x, y, r - 1, start_color);
	aacircleColor(renderer, x, y, r - thickness, end_color);

}

void Draw::arc(SDL_Renderer* renderer, int x, int y, int r, Uint32 color, size_t arc_num)
{
	Uint8* c = (Uint8*)& color;
	SDL_SetRenderDrawColor(renderer, c[3], c[2], c[1], c[0]);

	double n = -M_PI / 1000;
	double x1, y1;

	double start = 0;
	double end = 0;

	switch (arc_num)
	{
	case 1:
	{
		start = M_PI;
		end = 3 * M_PI / 2;
		break;
	}
	case 2:
	{
		start = 3 * M_PI / 2;
		end = 2 * M_PI;
		break;
	}
	case 3:
	{
		start = 0;
		end = M_PI / 2;
		break;
	}
	case 4:
	{
		start = M_PI / 2;
		end = M_PI;
		break;
	}

	default:break;
	}

	n = start;

	while (n <= end)
	{
		n = n + M_PI / 1000;
		x1 = round(r * cos(n));
		y1 = round(r * sin(n));

		SDL_RenderDrawPoint(renderer, x + x1, y + y1);
	}
}

void Draw::arc(SDL_Renderer* renderer, int x, int y, int r, Uint32 color, size_t arc_num, size_t thickness)
{
	for (size_t i = 0; i < thickness; i++)
	{
		arc(renderer, x, y, r + i, color, arc_num);
	}
}

void Draw::arc(SDL_Renderer* renderer, int x, int y, int r, Uint32 start_color, Uint32 end_color, size_t arc_num, size_t thickness)
{
	Uint8* sc = (Uint8*)& start_color;
	Uint8* ec = (Uint8*)& end_color;



	int dr = sc[3] - ec[3];
	int dg = sc[2] - ec[2];
	int db = sc[1] - ec[1];
	int da = sc[0] - ec[0];


	for (size_t i = 0; i < thickness; i++)
	{
		double progress = i / (double)thickness;

		Uint32 temp_color = start_color;
		Uint8* tc = (Uint8*)& temp_color;

		tc[3] -= progress * dr;
		tc[2] -= progress * dg;
		tc[1] -= progress * db;
		tc[0] -= progress * da;

		Uint32 result_color = *(Uint32*)tc;

		arc(renderer, x, y, r + i, result_color, arc_num);
	}

}

void Draw::hline(SDL_Renderer* renderer, int x1, int y, int x2, Uint32 start_color, Uint32 end_color, size_t thickness)
{

	Uint8* sc = (Uint8*)& start_color;
	Uint8* ec = (Uint8*)& end_color;



	int dr = sc[3] - ec[3];
	int dg = sc[2] - ec[2];
	int db = sc[1] - ec[1];
	int da = sc[0] - ec[0];


	for (size_t i = 0; i < thickness; i++)
	{
		double progress = i / (double)thickness;

		Uint32 temp_color = start_color;
		Uint8* tc = (Uint8*)& temp_color;

		tc[3] -= progress * dr;
		tc[2] -= progress * dg;
		tc[1] -= progress * db;
		tc[0] -= progress * da;

		Uint32 result_color = *(Uint32*)tc;

		SDL_SetRenderDrawColor(renderer, tc[3], tc[2], tc[1], tc[0]);
		SDL_RenderDrawLine(renderer, x1, y + i, x2, y +i);
	}

	//aacircleColor(renderer, x, y, r - 1, start_color);
	//aacircleColor(renderer, x, y, r - thickness, end_color);

}

void Draw::vline(SDL_Renderer* renderer, int x, int y1, int y2, Uint32 start_color, Uint32 end_color, size_t thickness)
{

	Uint8* sc = (Uint8*)& start_color;
	Uint8* ec = (Uint8*)& end_color;



	int dr = sc[3] - ec[3];
	int dg = sc[2] - ec[2];
	int db = sc[1] - ec[1];
	int da = sc[0] - ec[0];


	for (size_t i = 0; i < thickness; i++)
	{
		double progress = i / (double)thickness;

		Uint32 temp_color = start_color;
		Uint8* tc = (Uint8*)& temp_color;

		tc[3] -= progress * dr;
		tc[2] -= progress * dg;
		tc[1] -= progress * db;
		tc[0] -= progress * da;

		Uint32 result_color = *(Uint32*)tc;

		SDL_SetRenderDrawColor(renderer, tc[3], tc[2], tc[1], tc[0]);
		SDL_RenderDrawLine(renderer, x + i, y1, x + i, y2);
	}


}

void Draw::roundedShadowRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int r, Uint32 start_color, Uint32 end_color, size_t shadowThickness, size_t shadowBlur)
{
	/*Draw::arc(renderer, x + r, y + r, r, start_color, end_color, 1, shadowThickness);

	Draw::hline(renderer, x + r, y - shadowThickness, x + w - r, end_color, start_color, shadowThickness);

	Draw::arc(renderer, x + w - r, y + r, r, start_color, end_color, 2, shadowThickness);

	Draw::vline(renderer, x + w, y + r, y + h - r, start_color, end_color, shadowThickness);

	Draw::arc(renderer, x + w - r, y + h - r, r, start_color, end_color, 3, shadowThickness);

	Draw::hline(renderer, x + r, y + h, x + w - r, start_color, end_color, shadowThickness);

	Draw::arc(renderer, x + r, y + h - r, r, start_color, end_color, 4, shadowThickness);

	Draw::vline(renderer, x - shadowThickness, y + r, y + h - r, end_color, start_color, shadowThickness);*/

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	Uint8* sc = (Uint8*)& start_color;
	Uint8* ec = (Uint8*)& end_color;



	int dr = sc[3] - ec[3];
	int dg = sc[2] - ec[2];
	int db = sc[1] - ec[1];
	int da = sc[0] - ec[0]; 


	



	if (shadowBlur <= shadowThickness)
	{
		for (size_t i = 0; i < shadowThickness - shadowBlur; i++)
		{
			Draw::roundedRectangle(renderer, x - i, y - i, w + 2 * i, h + 2 * i, r + i, start_color);
		}

		for (size_t i = shadowThickness - shadowBlur, j = 0; i < shadowThickness, j < shadowBlur; i++, j++)
		{
			double progress = j / (double)(shadowBlur);

			Uint32 temp_color = start_color;
			Uint8* tc = (Uint8*)& temp_color;

			tc[3] -= progress * dr;
			tc[2] -= progress * dg;
			tc[1] -= progress * db;
			tc[0] -= progress * da;

			Uint32 result_color = *(Uint32*)tc;


			Draw::roundedRectangle(renderer, x - i, y - i, w + 2 * i, h + 2 * i, r + i, result_color);
		}

	}
	else
	{
		for (size_t i = 0; i < shadowBlur; i++)
		{
			double progress = i / (double)(shadowBlur);

			Uint32 temp_color = start_color;
			Uint8* tc = (Uint8*)& temp_color;

			tc[3] -= progress * dr;
			tc[2] -= progress * dg;
			tc[1] -= progress * db;
			tc[0] -= progress * da;

			Uint32 result_color = *(Uint32*)tc;


			Draw::roundedRectangle(renderer, x - i, y - i, w + 2 * i, h + 2 * i, r + i, result_color);
		}
	}

}

void Draw::roundedRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int r, Uint32 color)
{
	Draw::arc(renderer, x + r, y + r, r, color, 1);

	Draw::hline(renderer, x + r, y, x + w - r, color);

	Draw::arc(renderer, x + w - r, y + r, r, color, 2);

	Draw::vline(renderer, x + w, y + r, y + h - r, color);

	Draw::arc(renderer, x + w - r, y + h - r, r, color, 3);

	Draw::hline(renderer, x + r, y + h, x + w - r, color);

	Draw::arc(renderer, x + r, y + h - r, r, color, 4);

	Draw::vline(renderer, x, y + r, y + h - r, color);
}

void Draw::hline(SDL_Renderer* renderer, int x1, int y, int x2, Uint32 color)
{
	Uint8* tc = (Uint8*)&color;
	SDL_SetRenderDrawColor(renderer, tc[3], tc[2], tc[1], tc[0]);
	SDL_RenderDrawLine(renderer, x1, y, x2, y);
}

void Draw::vline(SDL_Renderer* renderer, int x, int y1, int y2, Uint32 color)
{
	Uint8* tc = (Uint8*)& color;
	SDL_SetRenderDrawColor(renderer, tc[3], tc[2], tc[1], tc[0]);
	SDL_RenderDrawLine(renderer, x, y1, x, y2);
}
