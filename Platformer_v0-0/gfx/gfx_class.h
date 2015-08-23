#ifndef GFX_CLASS_H
#define GFX_CLASS_H

/*
 * Il namespace gfx_class contiene una serie di funzioni che veicolano solo
 * la gestione video. Ne fanno parte:
 *      la gestione della finestra
 *      la gestione degli sprite
 *      la gestione della view
 *      la gestione dei frame
 *      la gestione dell'animazione
 *
 * */

#include <SDL.h>
#include "window.h"

namespace gfx {
    extern Window *MainWindow;
    // avviare questa funzione prima di tutto
    void gfx_init();
    // aggiorna il frame
    void update();
    void clear_screen();
    void render_screen();
    // avviare questa funzione quando si esce
    void gfx_quit();
    SDL_Renderer* _get_render();

    // funzione di fade-in
    void set_fadein();

    SDL_Colour get_old_colour();
    void set_old_colour(const SDL_Colour& old);
}

#endif // GFX_CLASS_H
