#pragma once
#include "SDL.h"

#include "point.h"

class Mouse
{
private:
    static Mouse* instance;
    Mouse();

private:
    static Mouse* get_instance();


private:
    int x, y;
    int rel_x, rel_y;

public:
    static Point pos();
    static Point rel();
};


