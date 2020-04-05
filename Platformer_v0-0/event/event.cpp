#include "event.h"

static SDL_Event ev;

int event::_update_ev()
{
    return SDL_PollEvent(&ev);
}

event_types event::get_type()
{
    return static_cast<event_types>(ev.type);
}

SDL_Scancode event::get_key()
{
    return ev.key.keysym.scancode;
}

const Uint8* keystate::get_keystate(int *lenght)
{
    return SDL_GetKeyboardState(lenght);
}
