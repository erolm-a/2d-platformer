#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdlib>

#include "init.h"
#include "gfx/gfx_class.h"

void load_media()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0) {
        SDL_Log("Errore nell'inizializzazione: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        SDL_Log("Errore fatale in gfx_class alla linea %d: %s\n",
                __LINE__ - 2, IMG_GetError());
        exit(EXIT_FAILURE);
    }
    atexit(IMG_Quit);

    // inizializza finestra, renderer
    gfx::gfx_init();
    atexit(gfx::gfx_quit);

    // inizializza SDL_ttf e mixer
    if(TTF_Init() < 0) {
        SDL_Log("Errore fatale in load_media alla linea %d: %s\n",
                __LINE__ - 2, IMG_GetError());
        exit(EXIT_FAILURE);
    }
    atexit(TTF_Quit);
}
