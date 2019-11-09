#include "simple-rect.h"

SDL_Rect SimpleRect::toSdlRect()
{
	return {x,y,w,h};
}
