#ifndef WINDOW_H
#define WINDOW_H

/*
 * La classe window: semplice wrapper che gestisce una finestra.
 * Usata solo per scopo interno all'engine.
 * */

#include <SDL_video.h>
#include <SDL_render.h>
#include <string>


class Window
{
    SDL_Window *win {nullptr};
public:
    // renderer ha più utilità di window, perciò è meglio renderlo pubblico.
    SDL_Renderer *renderer {nullptr};

    struct window_info {
        const char *title = "Platformer";
        int xpos = SDL_WINDOWPOS_CENTERED, ypos = xpos;
        int width = 640, height = 480;
        unsigned int other_flags_window = SDL_WINDOW_SHOWN;
        int def_driver = -1;
        unsigned int flags_renderer = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
    };

    // È prevista la garanzia di base, ovvero che la classe non avrà l'arbitrio di
    // uscire dal programma, ma soltanto di lanciare un'eccezione.

    Window(window_info);
    ~Window();

    // usare con molta cautela
    void rename_window(const char* title) {SDL_SetWindowTitle(this->win, title);}

    void get_size(int *w, int *h) const {SDL_GetWindowSize(win, w, h);}

    struct init_except {std::string err_message;};
};

#endif // WINDOW_H
