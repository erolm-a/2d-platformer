#include "window.h"

Window::Window(Window::window_info pref)
{
    if((win = SDL_CreateWindow(pref.title, pref.xpos, pref.ypos,
                              pref.width, pref.height, pref.other_flags_window))
                              == nullptr)
    {
        win = nullptr, renderer = nullptr;
        throw Window::init_except {SDL_GetError()};
    }
    if((renderer = SDL_CreateRenderer(win, pref.def_driver,
                                 pref.flags_renderer))
                                 == nullptr) {
        renderer = nullptr;
        SDL_DestroyWindow(win);
        win = nullptr;
        throw Window::init_except {SDL_GetError()};
    }
}

Window::~Window()
{
    if(renderer) SDL_DestroyRenderer(renderer);
    if(win) SDL_DestroyWindow(win);
}
