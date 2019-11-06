#include "mouse.h"

Mouse* Mouse::instance = nullptr;

Mouse::Mouse()
{

}

Mouse* Mouse::get_instance()
{
    if (instance == nullptr)
        return instance = new Mouse();

    return nullptr;
}

Point Mouse::pos()
{
    Mouse* m = Mouse::get_instance();

    SDL_GetMouseState(&m->x, &m->y);
    return Point(m->x, m->y);
}

Point Mouse::rel()
{
    Mouse* m = Mouse::get_instance();


    SDL_GetRelativeMouseState(&m->x, &m->y);
    SDL_GetMouseState(&m->x, &m->y);

    return Point(m->x, m->y);
}
