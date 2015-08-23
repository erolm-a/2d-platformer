#include "event.h"

SDL_Event ev;

int event::_update_ev()
{
    return SDL_PollEvent(&ev);
}

event_types event::get_type()
{
    return static_cast<event_types>(ev.type);
}

auto event::get_key() -> decltype(key_codes::A)
{
    return ev.key.keysym.scancode;
}

const Uint8* keystate::get_keystate(int *lenght)
{
    return SDL_GetKeyboardState(lenght);
}
